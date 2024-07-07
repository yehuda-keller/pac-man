#include "GameBoard.h"

GameBoard::GameBoard()
    :m_LevelSize(0, 0), m_BoardTileSize(0, 0)
{}

//create the game board
void GameBoard::createBoard()
{
	createBoradBase();
	createGrid();
}

//create the game frame
void GameBoard::createBoradBase()
{
    //check what is the max size for each tile with the given level size
    //when we limit the game board to 900x700 pixels
    while (m_BoardTileSize.x * m_LevelSize.x <= 900.f && m_BoardTileSize.y * m_LevelSize.y <= 700.f)
    {
        m_BoardTileSize.x++;
        m_BoardTileSize.y++;
    }
    auto size = sf::Vector2f(m_BoardTileSize.x * m_LevelSize.x, m_BoardTileSize.y * m_LevelSize.y);
    auto position = sf::Vector2f(500, 400);//the center of the area for the game board
    m_gameBaseBoard = createShape(size, position,10);
}

//crate the background grid-with this grid we will get the following data:
//1)size 2)first position
void GameBoard::createGrid()
{
    //define the center of a tile 
    auto middleTile = sf::Vector2f(m_BoardTileSize.x / 2, m_BoardTileSize.y / 2);
    //define the topleft point of the game frame
    auto point = sf::Vector2f(500 - (m_BoardTileSize.x * m_LevelSize.x / 2), 400 - (m_BoardTileSize.y * m_LevelSize.y / 2));
    //define the position of the first tile(the top left tile)
    auto firstPosition = sf::Vector2f(point.x + middleTile.x, point.y + middleTile.y);
    //create the grid
    for (int row = 0; row < m_LevelSize.y; row++)
    {
        std::vector <sf::RectangleShape> vec;

        for (int col = 0; col < m_LevelSize.x; col++)
        {
            auto Position = sf::Vector2f(firstPosition.x + col * m_BoardTileSize.x,
                firstPosition.y + row * m_BoardTileSize.y);
            vec.push_back(createShape(m_BoardTileSize, Position, 0));
        }
        m_board.push_back(vec);
    }
}

//draw function
void GameBoard::DrawBoard(sf::RenderWindow& window)
{
    window.draw(m_gameBaseBoard);//draw frame
    for (int row = 0; row < m_LevelSize.y; row++)//draw the grid
        for (int col = 0; col < m_LevelSize.x; col++)
            window.draw(m_board[row][col]);
}

//set level size function
void GameBoard::setLevelSize(int width, int height)
{
    m_LevelSize.x = width;
    m_LevelSize.y = height;
}

//get level size function
sf::Vector2i GameBoard::getLevelSize() const
{
    return m_LevelSize;
}

//get tile function
//return tile in some position on the grid
sf::RectangleShape GameBoard::getTile(int row, int col)
{
    return m_board[row][col];
}

//erase all the data when we do restart or moving to the next level
void GameBoard::restart()
{
    for (int row = 0; row < m_LevelSize.y; row++)
            m_board[row].clear();
    m_board.clear();
    setLevelSize(0, 0);
    m_BoardTileSize.x = 0;
    m_BoardTileSize.y = 0;
}
