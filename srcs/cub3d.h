/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:39:08 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 18:31:52 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef C_S
#  define C_S 1
# endif
# ifndef FOV
#  define FOV 66.
# endif
# ifndef DEG_STEP
#  define DEG_STEP 4.
# endif
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <time.h>

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESCAPE 53
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_EXIT 17

typedef struct	s_spr{
	int			sprite_x;
	int			sprite_y;
	int			s_column;
	int			end_column;
	double		distance;
	double		angle;
	int			pos_counter;
}				t_spr;

typedef struct	s_textures {
	int			texture;
	double		angle;
	double		t_distance;
	double		t_position;
	double		t_s_distance;
}				t_textures;

typedef struct	s_calc
{
	double		ray_angle;
	double		x_0;
	double		y_0;
	double		rad_ray_angle;
	double		rad_player_angle;
	int			x;
	int			y;
	double		dx;
	double		dy;
	double		xstep;
	double		ystep;
	double		xh;
	double		yv;
	int			dirx;
	int			diry;
	double		distance_h;
	double		distance_v;
}				t_calc;

typedef struct	s_fov {
	int			size;
	double		player_angle;
	t_calc		vars;
	t_textures	*trace_result;
	int			found_sprites;
	t_spr		*sprites;
}				t_fov;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct	s_pos {
	double		x_p;
	double		y_p;
	double		deg_p;
	double		angle_step;
}				t_pos;

typedef struct	s_frame {
	t_vars		*vars;
	int			size_x;
	int			size_y;
	int			fov_size;
	int			move_fw;
	int			move_bw;
	int			move_l;
	int			move_r;
	int			rotate_r;
	int			rotate_l;
	t_data		*img;
	t_fov		*fov;
	t_pos		*player;
}				t_frame;

typedef struct	s_params
{
	int			resolution_x;
	int			resolution_y;
	t_data		*textures[5];
	int			texture_dims[5][2];
	int			floor_color[3];
	int			ceilling_color[3];
	char		**map;
	int			max_row;
	int			*max_x;
	int			x_position;
	int			y_position;
	char		heading;
	int			start;
	int			num_sprites;
	t_frame		*frame;
}				t_params;

extern t_params	*g_params;
int				init_params(void *mlx);
int				init_map(char *str, void *mlx);
int				free_tab(char **tab, int nb);
void			clean_g_params(void);
int				exit_with_error(int error, char *str);
int				alloc_map_rows(void);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			run();
int				append_line(char *str);
int				add_color(char **res, char c);
int				add_resolution(char *str, void *mlx_ptr);
int				add_sprite(char **str, void *mlx_ptr);
double			normalize_angle(double x);
t_fov			*calculate_fov(t_params *map, t_fov *fov, double x_0,
double y_0);
double			to_radians(double degrees);
void			check_for_valid_map(char **map);
void			print_line(int x, int line_length, int texture,
int texture_column);
int				get_color(t_data *data, int x, int y);
void			print_fov(t_fov *fov);
void			print_sprites(t_fov *fov, int i);
void			set_params(int *height_offset, double *cur_row,
int *line_length, double row_step);
void			color_fill(t_frame *frame, int sky, int floor, t_data img);
int				create_trgb(int t, int r, int g, int b);
int				key_release(int keycode, t_frame *frame);
int				key(int keycode, t_frame *frame);
int				render_frame(t_frame *frame);
int				find_player_pos(char **map, int *result);
int				get_update(t_frame *frame);
int				check_valid_map(char **map, int y, int x);
void			update_player_pos(t_pos *player, double step, int i);
t_frame			*init_frame(void);
void			init_player(t_frame *frame);
void			init_fov(t_frame *frame);
t_calc			first_angle(t_calc vars);
t_calc			second_angle(t_calc vars);
t_calc			third_angle(t_calc vars);
t_calc			fourth_angle(t_calc vars);
void			result_one(t_calc vars, int step);
void			result_two(t_calc vars, int step);
void			result_three(t_calc vars, int step);
void			result_four(t_calc vars, int step);
double			sqrt_pw(double one, double two, double three, double four);
int				get_tex_dir(double angle, int vertical, int horizontal);
void			set_texture(int step, int direction, const double *params);
int				loop_spr(t_spr *sprites, int x, int y, int step);
void			check_sprites(int x, int y, int step, double angle);
void			process_r_sprites(double max_angle, int *step,
int i, int *prev_column);
void			process_l_sprites(double max_angle, int *step,
int i, int *prev_column);
void			set_sprites(t_fov *fov);
void			set_vars(t_calc *vars);
void			trace_ray(char **map, t_calc vars, int step);
void			calc_texture(t_calc vars, int step);
t_calc			set_vars_angle(t_calc vars);
t_calc			set_vars_in_tace_ray(t_calc vars);
void			prepare_data(double *min_angle, double *max_angle,
double x0, double y0);
int				cal_spr(t_spr *spr, double x_0, double y_0, int max_spr);
void			calc_max_x(void);
void			check_resolution(void *mlx_ptr);
int				loop_spr_border(t_spr *sprite, int step);
void			sort_sprites(t_spr *sprites, int num_spr, int i);
void			save_image(void);
void			ft_putstr(char *str);
int				line_is_param(char *str, void *mlx_ptr);
int				line_is_map(char *str);
int				check_name(char *str);
void			check_params(void);
int				red_cross(void);
void			rotate(t_frame *frame);
#endif
