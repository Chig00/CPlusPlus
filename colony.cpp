#include <iostream>
#include "sdlandnet.hpp"

constexpr const char* TITLE = "Colony by Chigozie Agomo";
constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;
constexpr int QUIT_KEY = Events::ESCAPE;
constexpr int RESET_KEY = Events::LETTERS['R' - 'A'];
constexpr int KILL_KEY = Events::LETTERS['K' - 'A'];
constexpr int CELL_WIDTH = 8;
constexpr int CELL_HEIGHT = 8;
constexpr int COLOUR_MIN = 3;
constexpr int COLOUR_MAX = 8;

class Cell {
    public:
        enum Mode {
            DIE,
            LIVE,
            SPLIT,
            PAUSED
        };
        
        Cell(
            int position_x = (WIDTH - CELL_WIDTH) / 2,
            int position_y = (HEIGHT - CELL_HEIGHT) / 2,
            int velocity_x = 1,
            int velocity_y = 0,
            int colour = COLOUR_MIN
        ) noexcept:
            position_x(position_x),
            position_y(position_y),
            velocity_x(velocity_x),
            velocity_y(velocity_y),
            colour(colour)
        {}
        
        std::vector<Cell> update(Display& display, Mode mode) noexcept {
            std::vector<Cell> children;
            
            if (mode != DIE) {
                display.fill(
                    Rectangle(
                        position_x - CELL_WIDTH / 2,
                        position_y - CELL_HEIGHT / 2,
                        CELL_WIDTH,
                        CELL_HEIGHT
                    ),
                    static_cast<Sprite::Colour>(colour)
                );
            }
            
            switch (mode) {
                case LIVE:
                    position_x += velocity_x;
                    position_y += velocity_y;
                    
                    if (position_x < 0) {
                        position_x = 1;
                        velocity_x *= -1;
                    }
                    
                    else if (position_x >= WIDTH) {
                        position_x = WIDTH - 2;
                        velocity_x *= -1;
                    }
                    
                    if (position_y < 0) {
                        position_y = 1;
                        velocity_y *= -1;
                    }
                    
                    else if (position_y >= HEIGHT) {
                        position_y = HEIGHT - 2;
                        velocity_y *= -1;
                    }
                    
                    break;
                
                case SPLIT:
                    children.push_back(
                        Cell(
                            position_x + velocity_y,
                            position_y + velocity_x,
                            velocity_y,
                            velocity_x,
                            colour_fix(colour + 1)
                        )
                    );
                    
                    children.push_back(
                        Cell(
                            position_x - velocity_y,
                            position_y - velocity_x,
                            -velocity_y,
                            -velocity_x,
                            colour_fix(colour - 1)
                        )
                    );
                    
                    break;
            }
            
            return children;
        }
    
    private:
        static int colour_fix(int colour) noexcept {
            if (colour < COLOUR_MIN) {
                colour = COLOUR_MAX;
            }
            
            else if (colour > COLOUR_MAX) {
                colour = COLOUR_MIN;
            }
            
            return colour;
        }
        
        int position_x;
        int position_y;
        int velocity_x;
        int velocity_y;
        int colour;
};

int main(int argc, char** argv) {
    double split_rate;
    double death_rate;
    double kill_rate;
    
    if (argc > 2) {
        split_rate = std::stod(argv[1]);
        death_rate = std::stod(argv[2]);
        kill_rate = std::stod(argv[3]);
    }
    
    else {
        std::cout << "Split Rate: ";
        std::cin >> split_rate;
        std::cout << "Death Rate: ";
        std::cin >> death_rate;
        std::cout << "Kill Rate: ";
        std::cin >> kill_rate;
    }
    
    System::initialise();
    
    {
        Display display(TITLE, WIDTH, HEIGHT);
        display.fill();
        
        std::vector<Cell> cells;
        cells.push_back(Cell());
        
        RNG generator;
        
        Event event;
        bool end = false;
        bool paused = false;
        
        while (!end) {
            display.fill();
            std::vector<int> dead_cells;
            std::vector<Cell> new_cells;
            
            for (int i = 0; i < cells.size(); ++i) {
                Cell::Mode mode = Cell::PAUSED;
                
                if (!paused) {
                    double luck = generator.get_double(0, 1);
                    
                    if (luck < death_rate) {
                        mode = Cell::DIE;
                        dead_cells.push_back(i);
                    }
                    
                    else if (luck > 1 - split_rate) {
                        mode = Cell::SPLIT;
                        dead_cells.push_back(i);
                    }
                    
                    else {
                        mode = Cell::LIVE;
                    }
                }
                
                std::vector<Cell> children(cells[i].update(display, mode));
                new_cells.insert(new_cells.end(), children.begin(), children.end());
            }
            
            for (int i = dead_cells.size() - 1; i >= 0; --i) {
                cells.erase(cells.begin() + dead_cells[i]);
            }
            
            cells.insert(cells.end(), new_cells.begin(), new_cells.end());
            
            display.update();
            
            while (!end && event.poll()) {
                switch (event.type()) {
                    case Event::TERMINATE:
                        end = true;
                        break;
                    
                    case Event::LEFT_UNCLICK:
                        paused = !paused;
                        break;
                    
                    case Event::MIDDLE_UNCLICK:
                        cells.clear();
                        cells.push_back(Cell());
                        break;
                    
                    case Event::RIGHT_UNCLICK:
                        for (int i = cells.size() - 1; i >= 0; --i) {
                            if (generator.get_real(0, 1) < kill_rate) {
                                cells.erase(cells.begin() + i);
                            }
                        }
                        
                        break;
                    
                    case Event::KEY_RELEASE:
                        if (event.key() == QUIT_KEY) {
                            end = true;
                        }
                        
                        else if (event.key() == RESET_KEY) {
                            cells.clear();
                            cells.push_back(Cell());
                        }
                        
                        else if (event.key() == KILL_KEY) {
                            for (int i = cells.size() - 1; i >= 0; --i) {
                                if (generator.get_real(0, 1) < kill_rate) {
                                    cells.erase(cells.begin() + i);
                                }
                            }
                        }
                        
                        else {
                            paused = !paused;
                        }
                        
                        break;
                }
            }
        }
    }
    
    System::terminate();
    
    return 0;
}