#ifndef TILE_H_
#define TILE_H_

struct Tile {
  int nb_tile;              //le numéro de la tuile
  int pas_blinky = 0;       //le nombre de pas que blinky doit faire pour arriver jusqu'a la case qu'il vise
  int pas_pinky_up = 0;     //le nombre de pas que pinky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est up
  int pas_pinky_down = 0;   //le nombre de pas que pinky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est down
  int pas_pinky_left = 0;   //le nombre de pas que pinky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est left
  int pas_pinky_right = 0;  //le nombre de pas que pinky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est right
  int pas_inky_up = 0;      //le nombre de pas que inky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est up
  int pas_inky_down = 0;    //le nombre de pas que inky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est down
  int pas_inky_left = 0;    //le nombre de pas que inky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est left
  int pas_inky_right = 0;   //le nombre de pas que inky doit faire pour arriver jusqu'a la case qu'il vise si la direction de pacman est right
  int pas_clyde = 0;        //le nombre de pas que clyde doit faire pour arriver jusqu'a la case qu'il vise
  float x;                  //la position x de la tuile
  float y;                  //la position y de la tuile
  int up_tile;              //le numéro de la tuile qui est au juste en haut, si c'est un mur la valeur sera égale à -1
  int down_tile;            //le numéro de la tuile qui est au juste en bas si c'est un mur la valeur sera égale à -1
  int left_tile;            //le numéro de la tuile qui est au juste à gauche si c'est un mur la valeur sera égale à -1
  int right_tile;           //le numéro de la tuile qui est au juste à droite si c'est un mur la valeur sera égale à -1
  bool done = false;        //true si on a déja calculé les pas pour cette tuile
  bool checked = false;     //true si on a vérifié toutes les tuiles adjacentes à celle ci
};

#endif
