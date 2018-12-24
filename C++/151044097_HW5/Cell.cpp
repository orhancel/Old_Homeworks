//
// Created by ORHAN on 26.11.2017.
//





#include "Cell.h"







int Cell::getRow() const {
    return row;
}

void Cell::setRow(int row) {
    this->row=row  ;
}

int Cell::getCol() const {
    return this->col;
}

void Cell::setCol(int col) {
    this->col=col;
}

char Cell::getType() const {
    return type;
}

void Cell::setType(char type) {
    this->type = type;
}

char Cell::getColumn() const {
    return column;
}

void Cell::setColumn(char column) {
    Cell::column = column;
}


