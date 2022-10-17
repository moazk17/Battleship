///////////////////////////////////////////////////////////////////////////// 
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:a
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: 
 
// 0 
//  
// Name: Moaz Mahran 
// login ID: mkgmahra 
//////////////////////////

#include "grid.h"
#include <stdbool.h>
#include <stdio.h>

const bool HORIZONTAL = false;
const bool VERTICAL = true;


// see grid.h
int grid_get_cell(const struct grid *g, int x, int y) {
  int cell = (y * 10) + x;
  
  if (cell > 99 || cell < 0) {
    return -1;
  } else if (g->cell[cell] == true) {
    return 1;
  } else {
    return 0;  
  }
}


// see grid.h
void grid_print(const struct grid *g) {
  printf("   0 1 2 3 4 5 6 7 8 9\n");
  int i = 0;
  int ascii = 65;
  while (i < 100) {
    if (i % 10 == 0) {
      printf("%c ", ascii);
      ++ascii;
    }
    printf("|");
    if (g->cell[i]) {
      printf("x");
    } else { 
      printf(" ");
    }
    if (i % 10 == 9) {
      printf("|\n");
    }
    ++i;
  }
}

bool check_array(const int a[], int len, int value) {
  int i = 0;
  while (i < len && a[i] != value) {
    ++i;
  }
  if (i == len) {
    return true;
  } else {
    return false;
  }
}

// see grid.h
bool grid_is_complete(const struct grid *g) {
  if (g->total_ships[0] == 4 && g->total_ships[1] == 3 &&  
      g->total_ships[2] == 2 && g->total_ships[3] == 1) {
    return true;
  } else { 
    return false;
  }
}

static bool valid_check(int x, int y, bool a[]) {
  
  int status = 0;
  if (x + 1 > 9) {
    ++status;
  } else if (!a[(y * 10) + x + 1]) {
    ++status;
  }
  if (x - 1 < 0) {
    ++status;
  } else if (!a[(y * 10) + x - 1]) {
    ++status;
  }
  if (y + 1 > 9) {
    ++status;
  } else if (!a[(y * 10) + x + 10]) {
    ++status;
  }
  if (y - 1 < 0) {
    ++status;
  } else if (!a[(y * 10) + x - 10]) {
    ++status;
  }
  if ((y == 0 && x >= 0 && x <= 9) || (x == 0 && y >= 0 && y <= 9)) 
  {
    ++status;
  } else if (!a[(y * 10) + x - 11]) {
    ++status;
  }
  if ((y == 0 && x >= 0 && x <= 9) || (x == 0 && y >= 0 && y <= 9)) 
  {
    ++status;
  } else if (!a[(y * 10) + x - 9]) {
    ++status;
  }
  if ((y == 9 && x >= 0 && x <= 9) || (x == 0 && y >= 0 && y <= 9)) 
  {
    ++status;
  } else if (!a[(y * 10) + x + 9]) {
    ++status;
  }
  if ((y == 9 && x >= 0 && x <= 9) || (x == 9 && y >= 0 && y <= 9)) 
  {
    ++status;
  } else if (!a[(y * 10) + x + 11]) {
    ++status;
  }
  if (status == 8) {
    return true;
  } else {
    return false;
  }
}

// see grid.h
bool grid_add_ship(struct grid *g, int x, int y, int size, bool orientation) {
  
  if (!orientation && (10 < x + size)) {
    return false;
  } else if (orientation && 10 < y + size) {
    return false;
  } else if ( size > 4 || size < 1) {
    return false;
  } else if (g->total_ships[size - 1] == 5 - size) {
    return false;
  } else if  (!valid_check(x, y, g->cell)) {
    return false;
  }  else if (orientation && 
              !valid_check(x, y + size - 1, g->cell)) {
    return false;
  } else if (!orientation && 
             !valid_check(x + size - 1, y, g->cell)) {
    return false;
  }  else {
     ++g->total_ships[size - 1];
    if (!orientation) {
      int i = 0;
      while (i < size) {
        g->cell[y * 10 + x + i] = true;
        ++i;
      }
    } else {
      int i = 0;
      while (i / 10 < size) {
        g->cell[y * 10 + x + i] = true;
        i += 10;
      }
    }
    return true;
  }    
}
