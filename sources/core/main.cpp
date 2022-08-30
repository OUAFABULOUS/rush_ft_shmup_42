/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:09:33 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/28 23:33:22 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>
#include "ft_shmup.hpp"
#include <string.h>

std::vector<SpaceShip>	g_allies;
std::vector<Weapon>	g_weapon;
std::vector<Pusher>	g_pusher;
std::vector<Missiles>	g_missiles;
std::vector<Objects>	g_objs;
std::vector<Patrol>	g_patrol;

int	ft_background(void *window, t_data *game)
{
	for (size_t i = 0; i < g_objs.size(); i++)
	{
		g_objs[i].aff_obj();
		if (g_objs[i].get_S() == '$' && g_objs[i].get_X_O() == g_allies[0].get_X() && g_objs[i].get_Y_O() == g_allies[0].get_Y()
			&& !game->mode)
		{
			if (game->hp < 3) 
				game->hp++;
		}
		if (g_objs[i].get_C() == METEOR && g_objs[i].get_X_O() == g_allies[0].get_X() && g_objs[i].get_Y_O() == g_allies[0].get_Y()
			&& game->mode)
			return (1);
		mvwaddch((WINDOW *)window, g_objs[i].get_X_O(), g_objs[i].get_Y_O(), g_objs[i].get_S() | COLOR_PAIR(g_objs[i].get_C() | A_BOLD));
	}
	refresh();
	return (0);
}

int	ft_turn(void *&window, int key, t_data *game)
{
	erase();
	for (size_t i = 0; i < g_allies.size(); i++)
	{
		g_allies[i].action(key, window);
		for (size_t i = 0; i < g_pusher.size(); i++)
		{
			if ((g_allies[0].get_Y() == g_pusher[i].get_Y() && g_pusher[i].get_X() == g_allies[0].get_X())
				|| (game->mode && g_pusher[i].get_Y() <= 0))
				return (1);
			g_pusher[i].action(window);
		}
		for (size_t i = 0; i < g_patrol.size(); i++)
		{
			if (g_allies[0].get_Y() == g_patrol[i].get_Y() && g_patrol[i].get_X() == g_allies[0].get_X())
				return (1);
			g_patrol[i].action(window);
			if ((game->loop % (60 * 4) == 0))
				g_patrol[i].go_front(window);
		}
	}
	for (size_t i = 0; i < g_weapon.size(); i++)
	{
		g_weapon[i].action(window);
		for (size_t j = 0; j < g_pusher.size(); j++)
		{
			if (g_weapon[i].get_Y() == g_pusher[j].get_Y() && g_pusher[j].get_X() == g_weapon[i].get_X())
			{
				g_weapon.erase(g_weapon.begin() + j);
				g_pusher.erase(g_pusher.begin() + j);
				game->score += PUSHER_POINT;
				game->frags += 1;
			}
		}
		for (size_t j = 0; j < g_patrol.size(); j++)
		{
			if (g_weapon[i].get_Y() == g_patrol[j].get_Y() && g_patrol[j].get_X() == g_weapon[i].get_X())
			{
				g_weapon.erase(g_weapon.begin() + j);
				g_patrol.erase(g_patrol.begin() + j);
				game->score += PATROL_POINT;
				game->frags += 1;
			}
		}
	}
	for (size_t i = 0; i < g_missiles.size(); i++)
	{
		g_missiles[i].shoot_action(window);
		if (g_allies[0].get_Y() == g_missiles[i].get_Y() && g_missiles[i].get_X() == g_allies[0].get_X())
		{
			game->hp--;
			g_missiles.erase(g_missiles.begin() + i);
		}
		if (game->hp <= 0)
			return (1);
		for (size_t j = 0; j < g_weapon.size(); j++)
		{
			if (g_weapon[j].get_Y() == g_missiles[i].get_Y() && g_missiles[i].get_X() == g_weapon[j].get_X())
			{
				g_weapon.erase(g_weapon.begin() + j);
				g_missiles.erase(g_missiles.begin() + i);
				game->score += BULLET_POINT;
			}
		}
		
	}
	wrefresh((WINDOW *)window);
	return (0);
}

void	ft_aff_ath(void *window, t_data game)
{
	const char *str2 = "NORMAL";
	const char *str3 = "HARDMODE";
	for (int i = 0; i <= COLS; i++)
		mvwprintw((WINDOW *)window, 10, i, "_");
	mvwprintw((WINDOW *)window, 5, 20, "Level Phase: %d\n", game.phase);
	mvwprintw((WINDOW *)window, 6, 20, "Frags: %d\n", game.frags);
	mvwprintw((WINDOW *)window, 5, 60, "SCORE: %d\n", game.score);
	mvwprintw((WINDOW *)window, 5, 80, "HP: %d\n", game.hp);
	if (game.mode == 1)
		mvwprintw((WINDOW *)window, 6, 80, "MODE: %s\n", str3);
	else
		mvwprintw((WINDOW *)window, 6, 80, "MODE: %s\n", str2);
	int w = 60;
	const char *str = "CPP INVADER\n";
	for (int j = 0; j <= 11; j++)
	{
		mvwaddch((WINDOW *)window, 1, w, str[j] | COLOR_PAIR(RED_STAR) | A_BOLD);
		w++;
	}

}

int	main(void)
{
	void		*window;
	int		key;
	int		x;
	int		y;
	int		lost;
	t_data	game;

	window = NULL;
	x = 10;
	y = 10;
	key = 0;
	lost = 0;
	std::srand(time(NULL));
	if (ft_init_screen(&window) == 1)
		return (0);
	g_allies.emplace_back(SpaceShip(20, 20));
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);

	Objects objs(STAR);
	game.loop = 0;
	game.phase = 1;
	game.score = 0;
	game.frags = 0;
	game.hp = HP;
	game.mode = 0;
	if (ft_menu(window, &game))
		return (endwin(), 0);
	ft_secure_nodelay(&window);
	while (1)
	{
		ft_spawn_mobs(game);
		ft_spawn_objs(&game);
		if (ft_turn(window, key, &game))
		{
			lost = 1;
			break;
		}
		if (ft_background(window, &game))
		{
			lost = 1;
			break;
		}
		if (game.score > 5000)
			break;
		ft_aff_ath(window, game);
		key = getch();
		if (key == KEY_ESC || key == 3)
			break;
		wrefresh((WINDOW *)window);
		std::this_thread::sleep_for(std::chrono::duration<double, std::ratio<1,60>>(1));
		game.loop++;
		if (game.score >= 250)
			game.phase = 2;
		if (game.score >= 750)
		{
			game.mode = 1;
			game.phase = 3;
		}
		refresh();
	}
	endwin();
	if (lost == 1)
	{
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "				YOU LOST WITH A SCORE OF " << game.score << " AND " << game.frags << " ENEMY KILLED" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
	else if (game.score > 5000)
	{
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "				YOU WIN WITH A SCORE OF " << game.score << " AND " << game.frags << " ENEMY KILLED" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
	return 0;
}
