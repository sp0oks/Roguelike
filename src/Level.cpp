#include <Level.hpp>

Level::Level(){}

Level::Level(sf::RenderWindow& window){
  // Load floor textures
  this->addTile("../resources/sprites/tile/floor.png", TILE::FLOOR);
  this->addTile("../resources/sprites/tile/floor_alt.png", TILE::FLOOR_ALT);

  // Load wall textures
  this->addTile("../resources/sprites/wall/wall_bottom_end.png", TILE::WALL_BOTTOM_END);
  this->addTile("../resources/sprites/wall/wall_bottom_left.png", TILE::WALL_BOTTOM_LEFT);
  this->addTile("../resources/sprites/wall/wall_bottom_right.png", TILE::WALL_BOTTOM_RIGHT);
  this->addTile("../resources/sprites/wall/wall_bottom_t.png", TILE::WALL_BOTTOM_T);
  this->addTile("../resources/sprites/wall/wall_intersection.png", TILE::WALL_INTERSECTION);
  this->addTile("../resources/sprites/wall/wall_side_left_end.png", TILE::WALL_SIDE_LEFT_END);
  this->addTile("../resources/sprites/wall/wall_side_left_t.png", TILE::WALL_SIDE_LEFT_T);
  this->addTile("../resources/sprites/wall/wall_side_right_end.png", TILE::WALL_SIDE_RIGHT_END);
  this->addTile("../resources/sprites/wall/wall_side_right_t.png", TILE::WALL_SIDE_RIGHT_T);
  this->addTile("../resources/sprites/wall/wall_side.png", TILE::WALL_SIDE);
  this->addTile("../resources/sprites/wall/wall_single.png", TILE::WALL_SINGLE);
  this->addTile("../resources/sprites/wall/wall_top_end.png", TILE::WALL_TOP_END);
  this->addTile("../resources/sprites/wall/wall_top_left.png", TILE::WALL_TOP_LEFT);
  this->addTile("../resources/sprites/wall/wall_top_right.png", TILE::WALL_TOP_RIGHT);
  this->addTile("../resources/sprites/wall/wall_top_t.png", TILE::WALL_TOP_T);
  this->addTile("../resources/sprites/wall/wall_top.png", TILE::WALL_TOP);

  generate();
  createPath(1, 1);
  calculateWalls();
}

void Level::draw(sf::RenderWindow& window){
  for(int i = 0; i < GRID_HEIGHT; i++){
    for(int j = 0; j < GRID_WIDTH; j++){
      window.draw(m_grid[i][j].sprite);
    }
  }
}

int Level::addTile(std::string filePath, TILE tileType){
  int textureID = TextureManager::addTexture(filePath);

  if(textureID < 0)
    return -1;
  else
    this->m_textureIDs[static_cast<int>(tileType)] = textureID;

  return textureID;
}

void Level::generate(){
  for(int i = 0; i < GRID_HEIGHT; i++){
    for(int j = 0; j < GRID_WIDTH; j++){
      if(i%2 && j%2){
        m_grid[i][j].type = TILE::EMPTY;
      }else{
        m_grid[i][j].sprite.setTexture(TextureManager::getTexture(m_textureIDs[static_cast<int>(TILE::WALL_SINGLE)]));
        m_grid[i][j].type = TILE::WALL_SINGLE;
      }
      m_grid[i][j].sprite.setPosition(TILE_SIZE*i, TILE_SIZE*j);
    }
  }
}

void Level::createPath(int columnIndex, int rowIndex){
    sf::Vector2i directions[] = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
    std::random_shuffle(std::begin(directions), std::end(directions));
    for(int i = 0; i < 4; i++){
      auto newX = directions[i].x + columnIndex;
      auto newY = directions[i].y + rowIndex;

      if(m_grid[newX][newY].type == TILE::EMPTY){
        auto wallX = directions[i].x/2 + columnIndex;
        auto wallY = directions[i].y/2 + rowIndex;

        m_grid[newX][newY].type = TILE::FLOOR;
        m_grid[newX][newY].sprite.setTexture(TextureManager::getTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

        m_grid[wallX][wallY].type = TILE::FLOOR;
        m_grid[wallX][wallY].sprite.setTexture(TextureManager::getTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

        createPath(newX, newY);
      }
    }
}

void Level::calculateWalls(){
  for(int i = 0; i < GRID_HEIGHT; i++){
    for(int j = 0; j < GRID_WIDTH; j++){
      if(m_grid[i][j].type != TILE::FLOOR){
        int score = 0;
        if(i > 0)
          score += (m_grid[i-1][j].type != TILE::FLOOR)?8:0;
        if(j < GRID_WIDTH-1)
          score += (m_grid[i][j+1].type != TILE::FLOOR)?4:0;
        if(i < GRID_HEIGHT-1)
          score += (m_grid[i+1][j].type != TILE::FLOOR)?2:0;
        if(j > 0)
          score += (m_grid[i][j-1].type != TILE::FLOOR)?1:0;
        m_grid[i][j].type = static_cast<TILE>(score);
        m_grid[i][j].sprite.setTexture(TextureManager::getTexture(m_textureIDs[score]));
      }
    }
  }
}
