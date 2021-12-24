/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:58:10 by donpark           #+#    #+#             */
/*   Updated: 2021/12/24 15:58:10 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODE_H
# define KEYCODE_H

# if defined(__APPLE__)
#  define MS_LEFT		1
#  define MS_RIGHT		2
#  define MS_WHEEL		3
#  define MS_UP			4
#  define MS_DOWN		5

#  define UP			126
#  define DOWN			125
#  define LEFT			123
#  define RIGHT			124
#  define ESC			53
#  define ENTER			36

#  define ENG_A			0
#  define ENG_B			11
#  define ENG_C			8
#  define ENG_D			2
#  define ENG_E			14
#  define ENG_F			3
#  define ENG_G			5
#  define ENG_H			4
#  define ENG_I			34
#  define ENG_J			38
#  define ENG_K			40
#  define ENG_L			37
#  define ENG_M			46
#  define ENG_N			45
#  define ENG_O			31
#  define ENG_P			35
#  define ENG_Q			12
#  define ENG_R			15
#  define ENG_S			1
#  define ENG_T			17
#  define ENG_U			32
#  define ENG_V			9
#  define ENG_W			13
#  define ENG_X			7
#  define ENG_Y			16
#  define ENG_Z			6

#  define NUM_1			18
#  define NUM_2			19
#  define NUM_3			20
#  define NUM_4			21
#  define NUM_5			23
#  define NUM_6			22
#  define NUM_7			26
#  define NUM_8			28
#  define NUM_9			25
#  define NUM_0			29
#  define MINUS			27
#  define PLUS			24

#  define L_SQUARE		33
#  define R_SQUARE		30
#  define COLON			41
#  define QUOTE			39
#  define COMMA			43
#  define DOT			47
#  define SLASH			44
#  define B_SLASH		42
#  define BACKTIK		50
#  define TAB			48
#  define CAPS_LOCK		272
#  define L_SHIFT		257
#  define R_SHIFT		258
#  define L_CTRL		256
#  define R_CTRL		269
#  define L_ALT			261
#  define R_ALT			262
#  define L_CMD			259
#  define R_CMD			260
#  define SPACE			49
#  define BACKSPACE		51

#  define F1			122
#  define F2			120
#  define F3			99
#  define F4			118
#  define F5			96
#  define F6			97
#  define F7			98
#  define F8			100
#  define F9			101
#  define F10			109
#  define F11			103
#  define F12			111

#  define INSERT		279
#  define DELETE		117
#  define HOME			115
#  define END			119
#  define PAGEUP		116
#  define PAGEDOWN		121

#  define PS			105
#  define SL			107
#  define PB			113

#  define NUMPAD_1		83
#  define NUMPAD_2		84
#  define NUMPAD_3		85
#  define NUMPAD_4		86
#  define NUMPAD_5		87
#  define NUMPAD_6		88
#  define NUMPAD_7		89
#  define NUMPAD_8		91
#  define NUMPAD_9		92
#  define NUMPAD_0		82
#  define NUMPAD_MINUS	78
#  define NUMPAD_PLUS	69
#  define NUMPAD_SLASH	75
#  define NUMPAD_STAR	67
#  define NUMPAD_ENTER	76
#  define NUMPAD_DOT	65
# else
#  define MS_LEFT		1
#  define MS_RIGHT		3
#  define MS_WHEEL		2
#  define MS_UP			4
#  define MS_DOWN		5

#  define UP			65362
#  define DOWN			65364
#  define LEFT			65361
#  define RIGHT			65363
#  define ESC			65307
#  define ENTER			65293

#  define ENG_A			97
#  define ENG_B			98
#  define ENG_C			99
#  define ENG_D			100
#  define ENG_E			101
#  define ENG_F			102
#  define ENG_G			103
#  define ENG_H			104
#  define ENG_I			105
#  define ENG_J			106
#  define ENG_K			107
#  define ENG_L			108
#  define ENG_M			109
#  define ENG_N			110
#  define ENG_O			111
#  define ENG_P			112
#  define ENG_Q			113
#  define ENG_R			114
#  define ENG_S			115
#  define ENG_T			116
#  define ENG_U			117
#  define ENG_V			118
#  define ENG_W			119
#  define ENG_X			120
#  define ENG_Y			121
#  define ENG_Z			122

#  define NUM_1			49
#  define NUM_2			50
#  define NUM_3			51
#  define NUM_4			52
#  define NUM_5			53
#  define NUM_6			54
#  define NUM_7			55
#  define NUM_8			56
#  define NUM_9			57
#  define NUM_0			48
#  define MINUS			45
#  define PLUS			61

#  define L_SQUARE		91
#  define R_SQUARE		93
#  define COLON			59
#  define QUOTE			39
#  define COMMA			44
#  define DOT			46
#  define SLASH			47
#  define B_SLASH		92
#  define BACKTIK		96
#  define TAB			65289
#  define CAPS_LOCK		65509
#  define L_SHIFT		65505
#  define R_SHIFT		65506
#  define L_CTRL		65507
#  define R_CTRL		65507
#  define L_ALT			65513
#  define R_ALT			65513
#  define WINDOW		65515
#  define CODE			65383
#  define SPACE			32
#  define BACKSPACE		65288

// #  define F1
#  define F2			65471
#  define F3			65472
#  define F4			65473
#  define F5			65474
#  define F6			65475
#  define F7			65476
#  define F8			65477
#  define F9			65478
#  define F10			65479
#  define F11			65480
#  define F12			65481

#  define INSERT		65379
#  define DELETE		65535
#  define HOME			65360
#  define END			65367
#  define PAGEUP		65365
#  define PAGEDOWN		65366

// #  define PS
#  define SL			65300
#  define PB			65299

// #  define NUMPAD_1		83
// #  define NUMPAD_2		84
// #  define NUMPAD_3		85
// #  define NUMPAD_4		86
// #  define NUMPAD_5		87
// #  define NUMPAD_6		88
// #  define NUMPAD_7		89
// #  define NUMPAD_8		91
// #  define NUMPAD_9		92
// #  define NUMPAD_0		82
// #  define NUMPAD_MINUS	78
// #  define NUMPAD_PLUS	69
// #  define NUMPAD_SLASH	75
// #  define NUMPAD_STAR	67
// #  define NUMPAD_ENTER	76
// #  define NUMPAD_DOT	65
# endif

#endif
