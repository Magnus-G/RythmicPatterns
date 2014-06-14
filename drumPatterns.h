// drums [z][y][x]

boolean drums[1][5][16] = {
  {
  // 1  2  3  4  5  6  7  8   1  2  3  4  5  6  7  8
    {1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0,  1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
  }

  // { // -1. sequence
  // // 1, 2, 3, 4, 5, 6, 7, 8,  1, 2, 3, 4, 5, 6, 7, 8
  //   {1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0},
  //   {0, 0, 1, 0, 0, 0, 0, 0,  0, 0, 1, 0, 0, 0, 0, 0},
  //   {0, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0},
  //   {0, 0, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 0, 0, 1, 0},
  //   {1, 1, 0, 0, 0, 1, 1, 0,  0, 0, 1, 1, 0, 0, 0, 1},
  // },
  
  // { // 0. straight
  // // 1, 2, 3, 4, 5, 6, 7, 8,  1, 2, 3, 4, 5, 6, 7, 8
  //   {1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0},
  //   {0, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0},
  //   {1, 0, 0, 0, 1, 0, 0, 0,  1, 0, 0, 0, 1, 0, 0, 0},
  //   {1, 0, 0, 1, 0, 0, 1, 0,  0, 1, 0, 0, 1, 0, 0, 0}, // synchopation
  //   {0, 0, 0, 1, 0, 0, 0, 1,  0, 0, 0, 1, 0, 0, 0, 1},
  // },
  
  // { // 1. double bd start
  // // 1, 2, 3, 4, 5, 6, 7, 8,  1, 2, 3, 4, 5, 6, 7, 8
  //   {1, 0, 1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
  //   {0, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
  //   {1, 0, 0, 0, 1, 0, 0, 0,  1, 0, 0, 0, 1, 0, 0, 0}, 
  //   {0, 0, 1, 0, 0, 1, 0, 0,  1, 0, 0, 1, 0, 0, 1, 0}, // synchopation   
  //   {0, 0, 0, 0, 1, 0, 0, 0,  0, 1, 0, 0, 0, 0, 1, 0},
  // },
  
  // { // 2. double bd and sn
  // // 1, 2, 3, 4, 5, 6, 7, 8,  1, 2, 3, 4, 5, 6, 7, 8
  //   {1, 0, 1, 0, 0, 0, 0, 0,  1, 0, 1, 0, 0, 0, 0, 0},
  //   {0, 0, 0, 0, 1, 0, 1, 0,  0, 0, 0, 0, 1, 0, 1, 0},
  //   {1, 0, 1, 0, 1, 0, 1, 0,  1, 0, 1, 0, 1, 0, 1, 0},
  //   {1, 0, 0, 1, 0, 0, 1, 0,  0, 1, 0, 0, 1, 0, 0, 0}, // synchopation
  //   {1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1},
  // },
  
  // { // 3. 
  // // 1, 2, 3, 4, 5, 6, 7, 8,  1, 2, 3, 4, 5, 6, 7, 8
  //   {1, 0, 0, 0, 0, 0, 1, 0,  1, 0, 0, 0, 0, 0, 0, 0},
  //   {0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0},
  //   {0, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0},
  //   {1, 0, 0, 0, 0, 1, 0, 0,  0, 0, 1, 0, 0, 0, 0, 0}, // synchopation
  //   {1, 1, 1, 0, 0, 1, 1, 1,  0, 0, 1, 1, 1, 0, 0, 1},
  // },
  
  // { // 5. 
  // // 1, 2, 3, 4, 5, 6, 7, 8,  1, 2, 3, 4, 5, 6, 7, 8
  //   {1, 0, 0, 0, 1, 0, 0, 0,  1, 0, 0, 0, 1, 0, 1, 1},
  //   {0, 0, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 0, 0, 0, 0},
  //   {1, 0, 0, 0, 1, 0, 0, 0,  1, 0, 0, 0, 1, 0, 0, 0},
  //   {1, 0, 0, 1, 0, 0, 1, 0,  0, 1, 0, 0, 1, 0, 0, 1}, // synchopation
  //   {1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 1, 1, 1, 1},
  // },    
  
  // { // 6. 
  // // 1, 2, 3, 4, 5, 6, 7, 8,  1, 2, 3, 4, 5, 6, 7, 8
  //   {1, 1, 0, 1, 1, 0, 1, 0,  1, 1, 0, 1, 0, 0, 1, 0},
  //   {0, 0, 1, 0, 0, 1, 0, 1,  0, 0, 1, 0, 1, 1, 0, 1},
  //   {1, 0, 1, 0, 1, 0, 1, 0,  1, 0, 1, 0, 1, 0, 1, 0},
  //   {1, 0, 0, 1, 0, 0, 1, 0,  0, 1, 0, 0, 1, 0, 0, 0}, // synchopation
  //   {1, 1, 1, 0, 0, 0, 1, 1,  1, 0, 0, 0, 1, 1, 1, 0},
  // }  
};