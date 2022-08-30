/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:20:44 by jtaravel          #+#    #+#             */
/*   Updated: 2022/08/28 18:37:11 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP

#define ENEMY_HPP

#include <iostream>
#include <string>

class	Enemy
{
	protected:
		int		_x;
		int		_y;
		int		_type;
		int		_pa;
		int		_pm;
		int		_pa_cost;
		int		_pm_cost;
		int		_dir;
		char	_shape;
		//int	_hp;
		int	_x_start;
		int	_y_start;
		virtual void	shoot(void);
		virtual void	movement(void);
		void			generate_pa_pm(void);
		void			display(void *&window);
		void			display(char shape, void *&window);
	public:
		Enemy(void);
		Enemy(const char &shape);
		Enemy(int type);
		Enemy(int x, int y, int type);
		Enemy(const Enemy &src);
		virtual ~Enemy(void);
		virtual int		get_X(void) const;
		virtual int		get_Y(void) const;
		virtual void	set_X(int x);
		virtual void	set_Y(int y);
		virtual void	setType(int type);
		void			action(void *&window);
};

#endif
