/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpaceShip.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:04:04 by jtaravel          #+#    #+#             */
/*   Updated: 2022/08/28 21:45:43 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.hpp"
#include <ncurses.h>
#include <chrono>
#include <thread>

SpaceShip::SpaceShip(void):_x(0),_y(0),_dir(ALLY)
{
	this->_shape = '>';
	return ;
}

SpaceShip::SpaceShip(int x, int y):_x(x),_y(y),_dir(ALLY)
{
	this->_shape = '>';
	return ;
}

SpaceShip::~SpaceShip(void)
{
	return ;
}

int	SpaceShip::get_X(void) const
{
	return (_x);
}

int	SpaceShip::get_Y(void) const
{
	return (_y);
}

void	SpaceShip::set_X(int x)
{
	_x = x;
}

void	SpaceShip::set_Y(int y)
{
	_y = y;
}

void	SpaceShip::shoot(void)
{
	g_weapon.emplace_back(Weapon(this->_x, this->_y, this->_dir, '-'));
}

void	SpaceShip::movement(int input)
{
	if (input == KEY_DOWN && _x + 1 < LINES)
		++_x;
	if (input == KEY_UP && _x - 1 > 10)
		--_x;
	if (input == KEY_LEFT && _y - 1 > 0)
		--_y;
	if (input == KEY_RIGHT && _y + 1 < COLS)
		++_y;
}

void	SpaceShip::display(void *&window)
{
	mvwaddch((WINDOW *)window, this->_x, this->_y, this->_shape | COLOR_PAIR(5) | A_BOLD);
}

void	SpaceShip::action(void *&window)
{
	(void)window;
}

void	SpaceShip::action(int input, void *&window)
{
	if (input == KEY_DOWN || input == KEY_UP || input == KEY_LEFT
		|| input == KEY_RIGHT)
		this->movement(input);
	if (input == KEY_SPACE)
		shoot();
	this->display(window);
}
