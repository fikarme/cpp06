// enum round_mode { round_half_up, round_half_down, round_bankers };

// double round( double , round_mode = round_half_up ) ;

// int main()
// {
//   round( 2.5, 42 );
//   // *** error: no implicit conversion from 'int' to 'round_mode'
// }

//in c++11, enums can be scoped or unscoped
//in c++98, enums are unscoped and can be used as integers
enum colour { RED, GREEN, BLUE }; // unscoped enum

struct printer { enum state { BUSY, IDLE, OFFLINE }; }; // unscoped enum at class scope

enum class direction { LEFT, RIGHT }; // scoped enum

int main()
{
    colour clr_sky = BLUE ;
    printer::state curr_state = printer::BUSY ;
    direction next_move = direction::RIGHT ;

    int a = clr_sky ; // imlicit conversion
    int b = printer::OFFLINE ; // imlicit conversion
    int c = int( direction::LEFT ) ; // explicit conversion

    clr_sky = colour(a) ; // explicit conversion
    curr_state = printer::state(b) ; // explicit conversion
    next_move = direction(c) ; // explicit conversion
}