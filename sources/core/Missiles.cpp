/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missiles.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:00:27 by jtaravel          #+#    #+#             */
/*   Updated: 2022/08/28 20:44:06 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.hpp"
#include "Missiles.hpp"

Missiles::Missiles(void)
{
	this->_x = Pusher::_x;
	this->_y = Pusher::_y;
	this->_pm = ENEMY_BULLET_1;
	this->_pm_cost = ENEMY_BULLET_1;
	this->_shape = '-';
}

Missiles::Missiles(int x, int y)
{
	this->_x = x;
	this->_y = y;
	this->_pm = ENEMY_BULLET_1;
	this->_pm_cost = ENEMY_BULLET_1;
	this->_shape = '-';
}

Missiles::~Missiles(void)
{
	return ;
}

void	Missiles::generate_pm(void)
{
	++this->_pm;
}

void	Missiles::movement(void)
{
	if (_pm >= _pm_cost)
	{
		--_y;
		_pm -= _pm_cost;
	}
	return ;
}

void	Missiles::shoot_action(void *&window)
{
	this->generate_pm();
	this->movement();
	this->display(_shape, window);
}
