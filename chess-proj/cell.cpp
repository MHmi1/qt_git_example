#include "cell.h"

Cell::Cell()
{


}

  Cell::~Cell()
  {


  }


void Cell::setPiece(std::unique_ptr<Piece> piece)
  {
        this->p = std::move(piece);
  }

  Piece * Cell::getPiece()
  {
      return  this->p.get();
  }
