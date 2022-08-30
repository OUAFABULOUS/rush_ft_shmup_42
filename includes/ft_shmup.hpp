/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:56:46 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/30 13:48:34 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_HPP
# define FT_SHMUP_HPP

#include <vector>
#include "SpaceShip.hpp"
#include "Enemy.hpp"
#include "Pusher.hpp"
#include "ncurses.h"
#include "Missiles.hpp"
#include "Weapon.hpp"
#include "Objects.hpp"
#include <memory>
#include "Objects.hpp"
#include "Patrol.hpp"

// GLOBALS BECAUSE WE CAN <3
extern std::vector<Enemy>	g_enemies;
extern std::vector<Weapon> g_weapon;
extern std::vector<SpaceShip> g_allies;
extern std::vector<Objects>	g_objs;
extern std::vector<Pusher> g_pusher;
extern std::vector<Missiles> g_missiles;
extern std::vector<Patrol> g_patrol;


# define FRAME_MS 16
//KEYS
# define KEY_ESC 27
# define KEY_CTRL_C 3
# define KEY_CTRL_D 4
# define KEY_SPACE 32

//ALLIES
#define ALLY 1

#define ALLY_SHAPE ">"
#define ALLY_PM 0

//ENEMIES

#define ENEMY -1
#define ENEMY_BULLET_1 10
#define ENEMY_BULLET_2 5
#define ENEMY_BULLET_3 1

#define STAY 0
#define PUSHER 1
#define PATROL 2
#define PATROL_Z 3
#define PUSHER_Z 4
#define PUSHER_UP 5
#define PUSHER_DOWN 6
#define PATROL_DOWN 7

//ENEMIES SHAPES
#define PUSHER_SHAPE '<'
#define STAY_SHAPE '0'
#define PATROL_SHAPE '8'
#define PUSHER_Z_SHAPE 'Z'
#define PUSHER_UP_SHAPE '\\'
#define PUSHER_DOWN_SHAPE '/'
#define PATROL_DOWN_SHAPE '8'

//ENEMIES COSTS
#define STAY_PA 0
#define PUSHER_PA 300
#define PATROL_PA 50
#define PATROL_Z_PA 0
#define PUSHER_Z_PA 0
#define PUSHER_UP_PA 0
#define PUSHER_DOWN_PA 0
#define PATROL_DOWN_PA 0

#define STAY_PM 0
#define PUSHER_PM 30
#define PATROL_PM 30
#define PATROL_Z_PM 0
#define PUSHER_Z_PM 0
#define PUSHER_UP_PM 0
#define PUSHER_DOWN_PM 0
#define PATROL_DOWN_PM 0

//STARS

#define STAR 0
#define RED_STAR 1
#define YELLOW_STAR 2
#define METEOR 3

//STARS

#define STAR 0
#define RED_STAR 1
#define YELLOW_STAR 2
#define METEOR 3

//ASCII




#define GO_0 "***\n"
#define GO_1 " *\n"
#define GO_2 " *\n"
#define GO_3 "        __ _   __ _  _ __ ___    ___    ___ __   __ ___  _ __ \n"
#define GO_4 "       / _` | / _` || '_ ` _ \\  / _ \\  / _ \\\\ \\ / // _ \\| '__|\n"
#define GO_5 "      | (_| || (_| || | | | | ||  __/ | (_) |\\ V /|  __/| |   \n"
#define GO_6 "       \\__, | \\__,_||_| |_| |_| \\___|  \\___/  \\_/  \\___||_|   \n"
#define GO_7 "        __/ |                                                 \n"
#define GO_8 "       |___/                                                  \n"
#define GO_9 " \n"

#define W_0 "\n"
#define W_1 "                                                    _ \n"
#define W_2 "                                                   | |\n"
#define W_3 "       _   _   ___   _   _  __      __ ___   _ __  | |\n"
#define W_4 "      | | | | / _ \\ | | | | \\ \\ /\\ / // _ \\ | '_ \\ | |\n"
#define W_5 "      | |_| || (_) || |_| |  \\ V  V /| (_) || | | ||_|\n"
#define W_6 "       \\__, | \\___/  \\__,_|   \\_/\\_/  \\___/ |_| |_|(_)\n"
#define W_7 "        __/ |                                         \n"
#define W_8 "       |___/                                          \n"
#define W_9 " \n"

#define FT_S0 "\n"
#define FT_S1 "        __  _              _                              "
#define FT_S2 "       / _|| |_       ___ | |__   _ __ ___   _   _  _ __  "
#define FT_S3 "      | |_ | __|     / __|| '_ \\ | '_ ` _ \\ | | | || '_ \\ "
#define FT_S4 "      |  _|| |_      \\__ \\| | | || | | | | || |_| || |_) |"
#define FT_S5 "      |_|   \\__|     |___/|_| |_||_| |_| |_| \\__,_|| .__/ "
#define FT_S6 "                                                  |_|    "
#define FT_S7 " "

typedef struct s_data
{
	int loop;
	int phase;
	int score;
	int frags;
}		t_data;


int		ft_init_screen(void **window);
int		ft_spawn_phase_1(t_data &game);
int		ft_spawn_phase_2(t_data &game);
int		ft_spawn_phase_3(t_data &game);
int		ft_spawn_mobs(t_data *game);
void	ft_spawn_objs(t_data *game);
int		ft_secure_nodelay(void **window);
//int		ft_menu(void *window);


#endif
