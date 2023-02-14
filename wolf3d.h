/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:52:01 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/30 13:37:45 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <time.h>
# include <stdint.h>

# define KEY_ESC 53
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_SPACE 49
# define KEY_Q 12
# define KEY_R	15
# define KEY_ENTER 36
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25
# define KEY_0 29
# define INT_MAX 2147483647
# define X 0
# define Y 1
# define Z 2
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 792
# define SCREEN_HEIGHT 792
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define NUM_SPRITES 25
# define MINIMAP_SIZE 192

/*				Map_for_Wolf3d
8 8 8 8 8 8 8 8 8 8 8 4 4 6 4 4 6 4 6 4 4 4 6 4 
8 0 0 0 0 0 0 0 0 0 8 4 0 0 0 0 0 0 0 0 0 0 0 4 
8 0 3 3 0 0 0 0 0 8 8 4 0 0 0 0 0 0 0 0 0 0 0 6 
8 0 0 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 6 
8 0 3 3 0 0 0 0 0 8 8 4 0 0 0 0 0 0 0 0 0 0 0 4 
8 0 0 0 0 0 0 0 0 0 8 4 0 0 0 0 0 6 6 6 0 6 4 6 
8 8 8 8 0 8 8 8 8 8 8 4 4 4 4 4 4 6 0 0 0 0 0 6 
7 7 7 7 0 7 7 7 7 0 8 0 8 0 8 0 8 4 0 4 0 6 0 6 
7 7 0 0 0 0 0 0 7 8 0 8 0 8 0 8 8 6 0 0 0 0 0 6 
7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 8 6 0 0 0 0 0 4 
7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 8 6 0 6 0 6 0 6 
7 7 0 0 0 0 0 0 7 8 0 8 0 8 0 8 8 6 4 6 0 6 6 6 
7 7 7 7 0 7 7 7 7 8 8 4 0 6 8 4 8 3 3 3 0 3 3 3 
2 2 2 2 0 2 2 2 2 4 6 4 0 0 6 0 6 3 0 0 0 0 0 3 
2 2 0 0 0 0 0 2 2 4 0 0 0 0 0 0 4 3 0 0 0 0 0 3 
2 0 0 0 0 0 0 0 2 4 0 0 0 0 0 0 4 3 0 0 0 0 0 3 
1 0 0 0 0 0 0 0 1 4 4 4 4 4 6 0 6 3 3 0 0 0 3 3 
2 0 0 0 0 0 0 0 2 2 2 1 2 2 2 6 6 0 0 5 0 5 0 5 
2 2 0 0 0 0 0 2 2 2 0 0 0 2 2 0 5 0 5 0 0 0 5 5 
2 0 0 0 0 0 0 0 2 0 0 0 0 0 2 5 0 5 0 5 0 5 0 5 
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 
2 0 0 0 0 0 0 0 2 0 0 0 0 0 2 5 0 5 0 5 0 5 0 5 
2 2 0 0 0 0 0 2 2 2 0 0 0 2 2 0 5 0 5 0 0 0 5 5 
2 2 2 2 1 2 2 2 2 2 2 1 2 2 2 5 5 5 5 5 5 5 5 5 
*/

typedef struct s_cast_floor
{
	double		raydirxy0[2];
	double		raydirxy1[2];
	int			p;
	double		posz;
	double		rowdistance;
	double		floorstepxy[2];
	double		floorxy[2];
	int			cellxy[2];
	int			tex_xy[2];
	int			floortex;
	int			ceilingtex;
	int			xy[2];
}	t_cast_floor;

typedef struct s_draw_sprite
{
	double		spritexy[2];
	double		invdet;
	double		transformxy[2];
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			drawstartend_xy[4];
	int			stripe;
	int			d;
	int			tex_xy[2];
	int			spriteorder[NUM_SPRITES];
	double		spritedistance[NUM_SPRITES];
}	t_draw_sprite;

typedef struct s_rc_wall
{
	double		camerax;
	double		raydirxy[2];
	int			mapxy[2];
	double		sidedistxy[2];
	double		deltadisxy[2];
	int			stepxy[2];
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			texnum;
	double		wallx;
	int			tex_xy[2];
	double		step;
	double		texpos;
	int			y;
}	t_rc_wall;

typedef enum e_sprite_type
{
	default_empty,
	soldier,
	shotgun
}	t_sprite_type;

typedef struct s_sprite
{
	double				x;
	double				y;
	int					texture;
	enum e_sprite_type	sprite_type;
	unsigned int		ignore_color;
}	t_sprite;

typedef enum e_gamemode
{
	edit,
	play
}	t_gamemode;

typedef struct s_file
{
	int		fd;
	int		gnl;
	int		size;
	char	*buffer;
	int		map_xy[2];
	int		has_read_file;
	int		error;
}	t_file;

typedef struct s_prm
{
	struct s_player	*player;
	struct s_ai_bot	*ai_bot;
	struct s_mlx	*mlx;
	struct s_render	*render;
	struct s_sprite	sprite[NUM_SPRITES];
	struct s_file	file;
	t_gamemode		gamemode;
	char			*filename;
}	t_prm;

typedef struct s_player
{
	int				worldmap[MAP_WIDTH][MAP_HEIGHT];
	double			posxy[2];
	double			dirxy[2];
	double			planexy[2];
	double			perpwalldist;
	clock_t			oldtime;
	double			delta_time;
	double			movespeed;
	double			rotspeed;
	int				currentframe;
	int				health;
	int				isdead;
	clock_t			timerdead;
	int				shotgun_tex;
	clock_t			shotgun_anim;
	char			onscreen_fps[10];
	int				save[24][24];
	int				compass_tex;
	int				move;
	int				turn;
}	t_player;

typedef enum e_type
{
	idle,
	follow,
	attack,
	regen,
	dead
}	t_type;

typedef struct s_pathfind
{
	double				g;
	double				h;
	double				f;
	int					vector[3];
	struct s_pathfind	*neighbor;
	struct s_pathfind	*next;
	struct s_pathfind	*parent;
}	t_pathfind;

typedef struct s_astar
{
	struct s_player		*player;
	struct s_ai_bot		*ai_bot;
	struct s_pathfind	*start;
	struct s_pathfind	*goal;
	struct s_pathfind	*current;
	struct s_pathfind	*openlist;
	struct s_pathfind	*closedlist;
	struct s_pathfind	*neighbor;
	struct s_pathfind	*openneighbor;
	struct s_pathfind	*head;
}	t_astar;

typedef struct s_ai_bot
{
	double				posxy[2];
	double				dirxy[2];
	enum e_type			mode;
	int					health;
	struct s_pathfind	*path;
	int					slowspeed;
}	t_ai_bot;

typedef struct s_render
{
	unsigned int	color;
	double			zbuffer[SCREEN_WIDTH];
	uint8_t			pngtex[16000];
	unsigned int	texture[12][TEX_HEIGHT * TEX_WIDTH];
	unsigned int	tex_soldier[17][TEX_HEIGHT * TEX_WIDTH];
	unsigned int	tex_shotgun[5][TEX_HEIGHT * TEX_WIDTH];
	char			filename[100];
}	t_render;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	char		*image_add;
	int			size_line;
	int			erdian;
	int			bpp;
}	t_mlx;

typedef struct s_recon_helper
{
	struct s_recon	*recon;
	uint8_t			*prev_color;
	int				type;
	unsigned int	*tex;
}	t_recon_helper;

typedef struct s_paeth_helper
{
	struct s_render	*render;
	int				xy[2];
	int				index;
	int				hex;
	unsigned int	*tex;
}	t_paeth_helper;

typedef struct s_recon
{
	t_render	*render;
	int			x;
	int			y;
	int			pos;
}	t_recon;

typedef struct s_paeth
{
	int	p;
	int	pa;
	int	pb;
	int	pc;
	int	pr;
}	t_paeth;

void			get_textures(t_render *render);
void			reconstruction_type_four(t_recon_helper *recon_helper);
void			reconstruction_type_three(t_recon_helper *recon_helper);
void			reconstruction_type_two(t_recon_helper *recon_helper);
void			reconstruction_type_one(t_recon_helper *recon_helper);
void			reconstruction_type_zero(t_recon_helper *recon_helper);
void			draw_sprites(t_prm *prm);
void			casting_floor(t_prm *prm);
void			raycasting_wall(t_prm *prm, int x);
void			wolf3d(t_prm *prm);
void			create_window(t_prm *prm);
int				keyboard_input(int key, void *ptr);
void			set_ray_pos(t_player *player, t_rc_wall *wall, int x);
void			step_direction(t_player *player, t_rc_wall *wall);
void			dda_algorithm(t_player *player, t_rc_wall *wall);
void			ai_bot_controller(t_prm *prm);
void			restart(t_prm *prm);
void			player_take_damage(int damage_amount, t_prm *prm);
void			player_controller(t_prm *prm);
void			player_shoot(t_prm *prm);
void			ai_bot_take_damage(int damage_amount, t_prm *prm);
void			draw_minimap(t_prm *prm);
void			edit_map(t_prm *prm);
void			exit_program(t_prm *prm, int is_error, char *error_msg);
void			draw_pixel(int x, int y, t_prm *prm);
void			check_valid_neighbors(t_astar *astar);
int				is_node(t_pathfind *node, t_pathfind *src);
t_pathfind		*neighbors(t_pathfind *node, t_player *player);
t_pathfind		*path_following(t_astar *astar);
t_pathfind		*remove_node(t_pathfind *node, t_pathfind *src);
t_pathfind		*add_node(t_pathfind *node, t_pathfind *head);
t_pathfind		*find_node(t_pathfind *node, t_pathfind *src);
void			get_next_path(t_prm *prm);
void			ai_bot_move(t_prm *prm);
void			ai_bot_dead(t_prm *prm);
void			ai_bot_walk_anim(t_prm *prm);
void			free_pathfind_lst(t_pathfind *lst);
int				input_key_up(int key, void *ptr);
int				input_key_down(int key, void *ptr);
void			player_turn_left(t_player *player);
void			player_turn_right(t_player *player);
void			player_move_forward(t_player *player);
void			player_move_backward(t_player *player);
void			open_file(t_prm *prm);
void			load_tex(t_render *render, char *filename, unsigned int *tex);
int				rgb_to_int(uint8_t Red, uint8_t Green, uint8_t Blue);
void			render_color(uint8_t *prev_color, t_render *render, int pos);
void			call_recon_func_type(t_recon_helper *recon_helper);
void			load_wall_textures(t_render *render);
void			load_sprite_textures(t_render *render);
void			load_soldier_textures(t_render *render);
void			load_shotgun_textures(t_render *render);
void			player_weapon(t_prm *prm);
void			player_health_bar(t_prm *prm);
void			end_screen(t_prm *prm);
void			sortsprites(t_draw_sprite *spr, t_prm *prm);
void			set_sprite_pos(t_draw_sprite *spr, t_prm *prm, int i);
void			sprite_width_height(t_draw_sprite *spr);
unsigned int	get_color_from_tex(t_prm *prm, t_draw_sprite *spr, int i);
int				paeth_helper(t_paeth_helper *paeth);
int				on_red_cross_exit(int key, void *ptr);
void			check_map(t_prm *prm);

#endif
