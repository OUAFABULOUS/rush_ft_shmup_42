/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:25:52 by jtaravel          #+#    #+#             */
/*   Updated: 2022/08/28 23:05:34 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.hpp"

Enemy::Enemy(void):_x (11+ (rand() % (LINES - 11))),_y (COLS - 1),_dir (ENEMY)
{
	_x_start = _x;
	_y_start = _y;
	_pm = 1;
	_pa = 1;
}

Enemy::Enemy(int type):_x(0),_y(0)
{
	_type = type;
	_x = rand() % LINES + 1;
	if (_x <= 10)
		_x += 10;
	_y = COLS - 6;
	_x_start = _x;
	_y_start = _y;
	_pm = 1;
	_pa = 1;
}

Enemy::Enemy(const char &shape):_shape(shape)
{
	_x = 11 + (rand() % (LINES - 11));
	_y = COLS - 1;
	_x_start = _x;
	_y_start = _y;
	_pm = 1;
	_pa = 1;
}

Enemy::Enemy(int x, int y, int type)
{
	_x = x;
	_y = y;
	_type = type;
}

Enemy::Enemy(const Enemy &src)
{
	*this = src;
}

Enemy::~Enemy(void)
{
	return ;
}

int	Enemy::get_X(void) const
{
	return (_x);
}

void	Enemy::setType(int type)
{
	_type = type;
}

int	Enemy::get_Y(void) const
{
	return (_y);
}

void	Enemy::set_X(int x)
{
	_x = x;
}

void	Enemy::set_Y(int y)
{
	_y = y;
}

void	Enemy::generate_pa_pm(void)
{
	this->_pa++;
	this->_pm++;
}

void	Enemy::shoot(void)
{
	return ;
}

void	Enemy::display(void *&window)
{
	mvwprintw((WINDOW *)window, this->_x, this->_y, "%c", _shape);
}

void	Enemy::display(char shape, void *&window)
{
	mvwprintw((WINDOW *)window, this->_x, this->_y, "%c", shape);
}

void	Enemy::action(void *&window)
{
	generate_pa_pm();
	if (this->_pa >= this->_pa_cost)
		shoot();
	if (this->_pm >= this->_pm_cost)
		movement();
	this->display(window);
}

void	Enemy::movement(void)
{
	return ;
}
