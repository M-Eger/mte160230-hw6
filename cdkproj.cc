// Micaelan Eger
// mte160230@utdallas.edu
// CS3377.002

#include <stdint.h>
#include <sstream>
#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
public:
  uint32_t		magicNumber;
  uint32_t		versionNumber;
  uint64_t		numRecords;
};

const int maxRecordStringLength=25;

class BinaryFileRecord
{
public:
  uint8_t		strLength;
  char			stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  char buffer[30];
  BinaryFileHeader *myRecord=new BinaryFileHeader();
  ifstream binInFile ("cs3377.bin",ios::in|ios::binary);

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /* Set up Magic number */
  binInFile.read(reinterpret_cast<char *>(&myRecord->magicNumber),sizeof(myRecord->magicNumber));
  sprintf(buffer,"Magic: %.8x",myRecord->magicNumber);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, buffer);
  drawCDKMatrix(myMatrix, true);    /* required  */

  
  /* Set up Version number */
  binInFile.read(reinterpret_cast<char *>(&myRecord->versionNumber),sizeof(myRecord->versionNumber));
  stringstream record2;
  record2<<"Version: "<<myRecord->versionNumber;

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 2, record2.str().c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */


  /* Set up records number */
  binInFile.read(reinterpret_cast<char *>(&myRecord->numRecords),sizeof(myRecord->numRecords));
  stringstream record3;
  record3<<"NumRecords: "<<myRecord->numRecords;

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 3, record3.str().c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */

  BinaryFileRecord *records=new BinaryFileRecord();
  stringstream tempRecord;

  /*
   * Read in records
   */
  for(int i=1;i<=(int)(myRecord->numRecords);i++){
    if(i<=4){
      tempRecord.str("");

      binInFile.read(reinterpret_cast<char *>(&records->strLength),sizeof(records->strLength));
      tempRecord<<"strlen: "<<records->strLength;
      setCDKMatrixCell(myMatrix, i+1, 1, tempRecord.str().c_str());
      drawCDKMatrix(myMatrix, true);
    
      binInFile.read(records->stringBuffer,sizeof(records->stringBuffer));
      setCDKMatrixCell(myMatrix, i+1, 2, records->stringBuffer);
      drawCDKMatrix(myMatrix, true);
    }
  }

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  binInFile.close();
  endCDK();
}
