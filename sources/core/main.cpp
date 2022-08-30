/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:09:33 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/30 13:49:31 by omoudni          ###   ########.fr       */
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

void	ft_background(void *window)
{
//	clear();
	for (size_t i = 0; i < g_objs.size(); i++)
	{
		g_objs[i].aff_obj();
		mvwaddch((WINDOW *)window, g_objs[i].get_X_O(), g_objs[i].get_Y_O(), g_objs[i].get_S() | COLOR_PAIR(g_objs[i].get_C() | A_BOLD));
	}
}

int	ft_replay(WINDOW *window)
{
	erase();
	int	ch;

	cbreak();
	mvwprintw(window, LINES / 2 - 5, COLS / 2 - 31, GO_0);
	mvwprintw(window, LINES / 2 - 4, COLS / 2 - 31, GO_1);
	mvwprintw(window, LINES / 2 - 3, COLS / 2 - 31, GO_2);
	mvwprintw(window, LINES / 2 - 2, COLS / 2 - 31, GO_3);
	mvwprintw(window, LINES / 2 - 1, COLS / 2 - 31, GO_4);
	mvwprintw(window, LINES / 2, COLS / 2 - 31, GO_5);
	mvwprintw(window, LINES / 2 + 1, COLS / 2 - 31, GO_6);
	mvwprintw(window, LINES / 2 + 2, COLS / 2 - 31, GO_7);
	mvwprintw(window, LINES / 2 + 3, COLS / 2 - 31, GO_8);
	mvwprintw(window, LINES / 2 + 4, COLS / 2 - 31, GO_9);
	mvwprintw(window, LINES - 3, COLS - 30,"press ENTER to play again");
	refresh();
	mvwprintw(window, LINES - 2, COLS - 30,"press ESC to quit");
	refresh();
	while ((ch = getch()))
	{
		if (ch == KEY_ESC)
			return (-1);
		if (ch == 10)
			return (1);
	}
	return (1);

}

int	ft_turn(void *&window, int key, t_data *game)
{
	clear();
	for (size_t i = 0; i < g_allies.size(); i++)
	{
		g_allies[i].action(key, window);
		for (size_t i = 0; i < g_pusher.size(); i++)
		{
			if (g_allies[0].get_Y() == g_pusher[i].get_Y() && g_pusher[i].get_X() == g_allies[0].get_X())
				return(ft_replay((WINDOW *)(window)));
			g_pusher[i].action(window);
		}
		for (size_t i = 0; i < g_patrol.size(); i++)
		{
			if (g_allies[0].get_Y() == g_patrol[i].get_Y() && g_patrol[i].get_X() == g_allies[0].get_X())
				return(ft_replay((WINDOW *)(window)));
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
				game->score += 5;
				game->frags += 1;
			}
		}
		for (size_t j = 0; j < g_patrol.size(); j++)
		{
			if (g_weapon[i].get_Y() == g_patrol[j].get_Y() && g_patrol[j].get_X() == g_weapon[i].get_X())
			{
				g_weapon.erase(g_weapon.begin() + j);
				g_patrol.erase(g_patrol.begin() + j);
				game->score += 10;
				game->frags += 1;
			}
		}
	}
	for (size_t i = 0; i < g_missiles.size(); i++)
	{
		g_missiles[i].shoot_action(window);
		if (g_allies[0].get_Y() == g_missiles[i].get_Y() && g_missiles[i].get_X() == g_allies[0].get_X())
			return(ft_replay((WINDOW *)(window)));
	}
	wrefresh((WINDOW *)window);
	return (0);
}

int	ft_menu(WINDOW *window)
{
	erase();
	int	ch;

	cbreak();
	mvwprintw((WINDOW *)window, 0, COLS / 2 - 29, FT_S0);
	mvwprintw((WINDOW *)window, 1, COLS / 2 - 29, FT_S1);
	mvwprintw((WINDOW *)window, 2, COLS / 2 - 29, FT_S2);
	mvwprintw((WINDOW *)window, 3, COLS / 2 - 29, FT_S3);
	mvwprintw((WINDOW *)window, 4, COLS / 2 - 29, FT_S4);
	mvwprintw((WINDOW *)window, 5, COLS / 2 - 29, FT_S5);
	mvwprintw((WINDOW *)window, 6, COLS / 2 - 29, FT_S6);
	mvwprintw((WINDOW *)window, 7, COLS / 2 - 29, FT_S7);
	mvwprintw((WINDOW *)window, LINES / 2, COLS / 2 - 12,"press ENTER to continue");
	mvwprintw((WINDOW *)window, LINES / 2 + 1, COLS / 2 - 12,"press ESC to quit");
	refresh();
	while ((ch = getch()))
	{
		if (ch == KEY_ESC)
			return (-1);
		if (ch == 10)
			return (0);
	}
	return (0);
}

void	ft_aff_ath(void *window, t_data game)
{
	for (int i = 0; i <= COLS; i++)
		mvwprintw((WINDOW *)window, 10, i, "_");
	mvwprintw((WINDOW *)window, 5, 20, "Level Phase: %d\n", game.phase);
	mvwprintw((WINDOW *)window, 6, 20, "Frags: %d\n", game.frags);
	mvwprintw((WINDOW *)window, 7, 20, "Score: %d\n", game.score);
	int w = COLS / 2 - 6;
	const char *str = "CPP INVADER\n";
	for (int j = 0; j <= 11; j++)
	{
		mvwaddch((WINDOW *)window, 1, w, str[j] | COLOR_PAIR(RED_STAR) | A_BOLD);
		w++;
	}

}

void	ft_init_game(t_data *game)
{
	game->loop = 0;
	game->phase = 1;
	game->score = 0;
	game->frags = 0;
}

int	ft_game_loop(void **window_ref, t_data *game, int loop)
{
	int		key;
	int		x;
	int		y;
	void	*window;
	(void)loop;

	window = *window_ref;
	x = 10;
	y = 10;
	key = 0;
	std::srand(time(NULL));
	if (!loop)
	{
	if (ft_init_screen(&window) == 1)
		return (0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	}
	g_allies.emplace_back(SpaceShip(20, 20));
	Objects objs(STAR);
	if (ft_menu((WINDOW *)window))
		return (endwin(), 0);
	erase();
	ft_secure_nodelay(&window);
	ft_init_game(game);
	while (1)
	{
		ft_spawn_mobs(game);
		ft_spawn_objs(game);
		int	ft_turne = ft_turn(window, key, game);
		if (ft_turne == -1)
			return (0);
		else if (ft_turne == 1)
			break ;
//		else
//			break;
//		if (ft_turn(window, key, game) == 1)
//			break ;
		ft_background(window);
		ft_aff_ath(window, *game);
		key = getch();
		if (key == KEY_ESC || key == 3)
			exit (1);
		wrefresh((WINDOW *)window);
		std::this_thread::sleep_for(std::chrono::duration<double, std::ratio<1,60>>(1));
		(game->loop)++;
	}
	g_allies.clear();
	g_objs.clear();
	g_weapon.clear();
	g_pusher.clear();
	g_missiles.clear();
	g_patrol.clear();
	ft_game_loop(&window, game, 1);
	return (0);
}

int	main(void)
{
	void		*window;
	t_data	game;
	window = NULL;

	ft_game_loop(&window , &game, 0);
	endwin();
	return 0;
}
