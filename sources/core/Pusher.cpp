/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pusher.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 08:45:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/28 19:01:33 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.hpp"
#include "Pusher.hpp"
#include "Pusher.hpp"

Pusher::Pusher(void): Enemy('<')
{
	this->_shape = '<';
	this->_pa_cost = PUSHER_PA;
	this->_pm_cost = PUSHER_PM;
}

Pusher::~Pusher(void)
{
	return ;
}

void	Pusher::shoot(void)
{
	this->_pa -= this->_pa_cost;
	g_missiles.emplace_back(Missiles(_x, _y));
	return ;
}

void	Pusher::movement(void)
{
	if (_pm >= _pm_cost)
	{
		--_y;
		_pm -= _pm_cost;
	}
	return ;
}
