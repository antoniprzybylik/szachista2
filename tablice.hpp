#pragma once

// wartości bierek

int wart[7] = { 0, 100, 320, 330, 500, 900, 20000 };

int pola[][8][8] = {

  { // nic

    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  0 }

  },

  { // pionek

    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 50, 50, 50, 50, 50, 50, 50, 50 },
    { 10, 10, 20, 30, 30, 20, 10, 10 },
    { 5,  5, 10, 25, 25, 10,  5,  5 },
    { 0,  0,  0, 20, 20,  0,  0,  0 },
    { 5, -5,-10,  0,  0,-10, -5,  5 },
    { 5, 10, 10,-20,-20, 10, 10,  5 },
    { 0,  0,  0,  0,  0,  0,  0,  0 }

  },

  { // skoczek

    { -50,-40,-30,-30,-30,-30,-40,-50 },
    { -40,-20,  0,  0,  0,  0,-20,-40 },
    { -30,  0, 10, 15, 15, 10,  0,-30 },
    { -30,  5, 15, 20, 20, 15,  5,-30 },
    { -30,  0, 15, 20, 20, 15,  0,-30 },
    { -30,  5, 10, 15, 15, 10,  5,-30 },
    { -40,-20,  0,  5,  5,  0,-20,-40 },
    { -50,-40,-30,-30,-30,-30,-40,-50 }

  },

  { // goniec

    { -20,-10,-10,-10,-10,-10,-10,-20 },
    { -10,  0,  0,  0,  0,  0,  0,-10 },
    { -10,  0,  5, 10, 10,  5,  0,-10 },
    { -10,  5,  5, 10, 10,  5,  5,-10 },
    { -10,  0, 10, 10, 10, 10,  0,-10 },
    { -10, 10, 10, 10, 10, 10, 10,-10 },
    { -10,  5,  0,  0,  0,  0,  5,-10 },
    { -20,-10,-10,-10,-10,-10,-10,-20 },

  },

  { // wieża

    { 0,  0,  0,  0,  0,  0,  0,  0 },
    { 5, 10, 10, 10, 10, 10, 10,  5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { -5,  0,  0,  0,  0,  0,  0, -5 },
    { 0,  0,  0,  5,  5,  0,  0,  0 }

  },

  { // hetman

    { -20,-10,-10, -5, -5,-10,-10,-20 },
    { -10,  0,  0,  0,  0,  0,  0,-10 },
    { -10,  0,  5,  5,  5,  5,  0,-10 },
    { -5,  0,  5,  5,  5,  5,  0, -5 },
    { 0,  0,  5,  5,  5,  5,  0, -5 },
    { -10,  5,  5,  5,  5,  5,  0,-10 },
    { -10,  0,  5,  0,  0,  0,  0,-10 },
    { -20,-10,-10, -5, -5,-10,-10,-20 }

  },

  { // król otwarcie

    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -30,-40,-40,-50,-50,-40,-40,-30 },
    { -20,-30,-30,-40,-40,-30,-30,-20 },
    { -10,-20,-20,-20,-20,-20,-20,-10 },
    { 20, 20,  0,  0,  0,  0, 20, 20 },
    { 20, 30, 10,  0,  0, 10, 30, 20 }

  },
  
  { // król koniec

    { -50,-40,-30,-20,-20,-30,-40,-50 },
    { -30,-20,-10,  0,  0,-10,-20,-30 },
    { -30,-10, 20, 30, 30, 20,-10,-30 },
    { -30,-10, 30, 40, 40, 30,-10,-30 },
    { -30,-10, 30, 40, 40, 30,-10,-30 },
    { -30,-10, 20, 30, 30, 20,-10,-30 },
    { -30,-30,  0,  0,  0,  0,-30,-30 },
    { -50,-30,-30,-30,-30,-30,-30,-50 }

  }

};
