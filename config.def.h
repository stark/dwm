/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[] = "-*-stlarch-medium-r-*-*-10-*-*-*-*-*-iso10646-1" ","
                           "-*-tamsyn-medium-r-normal-*-12-*-*-*-*-*-*-1";
static const char normbordercolor[] = "#1A1A1A";
static const char normbgcolor[]     = "#09090d";
static const char normfgcolor[]     = "#695C54";
static const char selbordercolor[]  = "#E5E5E5";
static const char selbgcolor[]      = "#09090d";
static const char selfgcolor[]      = "#9b9081";
static const unsigned int borderpx  = 3;            /* border pixel of windows */
static const unsigned int snap      = 0;            /* snap pixel */
static const unsigned int systraypinning = 0;       /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;       /* systray spacing */
static const Bool systraypinningfailfirst = True;   /* True: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const Bool showsystray       = True;         /* False means no systray */
static const Bool showbar           = True;         /* False means no bar */
static const Bool topbar            = True;         /* False means bottom bar */
static const Bool viewontag         = True;         /* Switch view on tag switch */

/* tagging */
static const char *tags[] = { "term", "www", "text", "file", "\uE09A", "games", "office", "\uE072 mail", "settings" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                      instance    title                          tags mask      iscentered               isfloating   monitor */
	{ "Gimp",                     NULL,       NULL,                          0,             False,                     True,        -1 },
	{ "Sxiv",                     NULL,       NULL,                          0,              True,                     True,        -1 },
	{ "XFontSel",                 NULL,       NULL,                          0,              True,                     True,        -1 },
	{  NULL,                      NULL,       "Event Tester",                0,             False,                     True,        -1 },
	{ "Message",                  NULL,       NULL,                          0,             False,                     True,        -1 },
	{ "Lxappearance",             NULL,       NULL,                          0,             False,                     True,        -1 },
	{ "Message",                  NULL,       NULL,                          0,             False,                     True,        -1 },
	{ "mpv",                      NULL,       NULL,                          0,             False,                    False,        -1 },
	{ "URxvt",                    NULL,       NULL,                          1 << 0,         True,                    False,        -1 },
	{ "URxvt",                    NULL,       "htop",                        1 << 0,        False,                     True,        -1 },
	{ "URxvt",                    NULL,       "ncmpcpp",                     1 << 0,         True,                     True,        -1 },
	{ "XTerm",                    NULL,       NULL,                          1 << 0,        False,                    False,        -1 },
	{ "Thunar",                   NULL,       NULL,                          1 << 3,        False,                    False,        -1 },
	{ "Thunar",                   NULL,       "File Operation Progress",     1 << 3,        False,                     True,        -1 },
	{ "Emacs",                    NULL,       NULL,                          1 << 2,        False,                    False,        -1 },
	{ "Chromium",                 NULL,       NULL,                          1 << 1,        False,                    False,        -1 },
	{ "Ario",                     NULL,       NULL,                          1 << 4,         True,                     True,        -1 },
	{ "fontforge",                NULL,       NULL,                          1 << 8,        False,                     True,        -1 },
	{ "Gbdfed",                   NULL,       NULL,                          1 << 8,         True,                     True,        -1 },
	{ "libreoffice*",             NULL,       NULL,                          1 << 6,        False,                    False,        -1 },
	{ "Zathura",                  NULL,       NULL,                          1 << 6,        False,                    False,        -1 },
	{ "libreoffice-writer",       NULL,       NULL,                          1 << 6,        False,                    False,        -1 },
	{ "Abiword",                  NULL,       NULL,                          1 << 6,        False,                    False,        -1 },
	{ "Gnumeric",                 NULL,       NULL,                          1 << 6,        False,                    False,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "push.c"
#include "focusmaster.c"
#include "toggleview_focus.c"
#include "exresize.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\uE000",    monocle },    /* first entry is default */
	{ "\uE0B1",    NULL },    /* no layout function means floating behavior */
	{ "\uE002",    tile },
	{ "[D]",       deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define HYPKEY Mod3Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ HYPKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
//#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char terminal[]       = "urxvtc";
static const char *termcmd[]       = { terminal, NULL };
static const char scratchpadname[] = "terminal";
static const char *scratchpadcmd[] = { terminal, "-name", scratchpadname, "-geometry", "140x30", NULL };


static Key keys[] = {
	/* modifier                     key                function                argument */
	{ MODKEY|ShiftMask,             XK_Return,         spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_p,              togglescratch,          {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,              togglebar,              {0} },
	
	{ MODKEY,                       XK_m,              focusmaster,            {0} },				/* requires: dwm-6.1-focusmaster.diff ( git apply )    */
	{ MODKEY,                       XK_s,              swapfocus,              {0} },				/* requires: dwm-6.1-swapfocus.diff   ( hand patched ) */ 
	
	{ MODKEY,                       XK_j,              focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,              focusstack,             {.i = -1 } },

	{ MODKEY,                       XK_i,              incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_d,              incnmaster,             {.i = -1 } },
	
	{ MODKEY,                       XK_h,              setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,              setmfact,               {.f = +0.05} },

	{ MODKEY|ShiftMask,             XK_h,              setcfact,               {.f = +0.25} },		/* Applies to Tile Layout only		requires: dwm-6.1-cfacts.diff ( hand patched ) */
	{ MODKEY|ShiftMask,             XK_l,              setcfact,               {.f = -0.25} },		/* Applies to Tile Layout only */
	{ MODKEY|ShiftMask,             XK_o,              setcfact,               {.f =  0.00} },		/* Applies to Tile Layout only */

	{ MODKEY,                       XK_Return,         zoom,                   {0} },				/* Swap Master */
	{ MODKEY,                       XK_Tab,            view,                   {0} },				/* Toggle between Current and previously active tag */
	{ MODKEY,                       XK_q,              killclient,             {0} },				/* Close Focused Window */

	{ MODKEY|ShiftMask,             XK_m,              setlayout,              {.v = &layouts[0]} },	/*  Monocle      */
	{ MODKEY|ShiftMask,             XK_f,              setlayout,              {.v = &layouts[1]} },	/*  Float        */
	{ MODKEY|ShiftMask,             XK_t,              setlayout,              {.v = &layouts[2]} },	/*  Tile         */
	{ MODKEY|ShiftMask,             XK_d,              setlayout,              {.v = &layouts[3]} },	/*  Deck         */

	{ MODKEY|ShiftMask,             XK_j,              pushdown,               {0} },
	{ MODKEY|ShiftMask,             XK_k,              pushup,                 {0} },

	{ MODKEY,                       XK_space,          setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,          togglefloating,         {0} },

	{ MODKEY|ALTKEY,                XK_space,          toggleview_focus,       {.ui = 1} },

	{ MODKEY,                       XK_0,              view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,              tag,                    {.ui = ~0 } },
	
	{ MODKEY,                       XK_Left,           cycle,                  {.i = -1 } },		 /* Cycle to the Previous Tag  */
	{ MODKEY,                       XK_Right,          cycle,                  {.i = +1 } },		 /* Cycle to the Next     Tag  */
	{ MODKEY|ShiftMask,             XK_Left,           tagcycle,               {.i = -1 } },		 /* Move focused window to the Previous Tag */
	{ MODKEY|ShiftMask,             XK_Right,          tagcycle,               {.i = +1 } },		 /* Move focused window to the Next     Tag */
	
	{ MODKEY,                       XK_comma,          focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,         focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,          tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,         tagmon,                 {.i = +1 } },

	/* Floating Window Manipulation 	requires: dwm-r1606-exresize.diff ( hand patched ) */

	{ MODKEY|HYPKEY,                XK_i,              explace,                {.ui = EX_NW }},		/* Teleport Window to the  Top    Left		*/
	{ MODKEY|HYPKEY,                XK_k,              explace,                {.ui = EX_N  }},		/* Teleport Window to the  Top    Center	*/
	{ MODKEY|HYPKEY,                XK_o,              explace,                {.ui = EX_NE }},		/* Teleport Window to the  Top    Right		*/
	{ MODKEY|HYPKEY,                XK_h,              explace,                {.ui = EX_W  }},		/* Teleport Window to the  Middle Left		*/
	{ MODKEY|HYPKEY,                XK_a,              explace,                {.ui = EX_C  }},		/* Teleport Window to the  Middle Center	*/
	{ MODKEY|HYPKEY,                XK_l,              explace,                {.ui = EX_E  }},		/* Teleport Window to the  Middle Right		*/
	{ MODKEY|HYPKEY,                XK_n,              explace,                {.ui = EX_SW }},		/* Teleport Window to the  Bottom Left		*/
	{ MODKEY|HYPKEY,                XK_j,              explace,                {.ui = EX_S  }},		/* Teleport Window to the  Bottom Center	*/
	{ MODKEY|HYPKEY,                XK_m,              explace,                {.ui = EX_SE }},		/* Teleport Window to the  Bottom Right		*/

	{ HYPKEY|ShiftMask,             XK_k,              exresize,               {.v = (int []){   0,  25 }}},
	{ HYPKEY|ShiftMask,             XK_j,              exresize,               {.v = (int []){   0, -25 }}},
	{ HYPKEY|ShiftMask,             XK_l,              exresize,               {.v = (int []){  25,   0 }}},
	{ HYPKEY|ShiftMask,             XK_h,              exresize,               {.v = (int []){ -25,   0 }}},
	{ HYPKEY|ShiftMask,             XK_a,              exresize,               {.v = (int []){  25,  25 }}},
	{ HYPKEY|ShiftMask|ControlMask, XK_a,              exresize,               {.v = (int []){ -25, -25 }}},

	{ HYPKEY|ALTKEY,                XK_l,              togglehorizontalexpand, {.i = +1} },
	{ HYPKEY|ALTKEY,                XK_m,              togglehorizontalexpand, {.i =  0} },
	{ HYPKEY|ALTKEY,                XK_h,              togglehorizontalexpand, {.i = -1} },
	{ HYPKEY|ALTKEY,                XK_k,              toggleverticalexpand,   {.i = +1} },
	{ HYPKEY|ALTKEY,                XK_n,              toggleverticalexpand,   {.i =  0} },
	{ HYPKEY|ALTKEY,                XK_j,              toggleverticalexpand,   {.i = -1} },
	{ HYPKEY|ALTKEY,                XK_i,              togglemaximize,         {.i = -1} },
	{ HYPKEY|ALTKEY,                XK_o,              togglemaximize,         {.i = +1} },
	{ HYPKEY|ALTKEY,                XK_a,              togglemaximize,         {.i =  0} },

	/* End of functions provided by dwm-r1606-exresize.diff */

	TAGKEYS(                        XK_1,                                      0)
	TAGKEYS(                        XK_2,                                      1)
	TAGKEYS(                        XK_3,                                      2)
	TAGKEYS(                        XK_4,                                      3)
	TAGKEYS(                        XK_5,                                      4)
	TAGKEYS(                        XK_6,                                      5)
	TAGKEYS(                        XK_7,                                      6)
	TAGKEYS(                        XK_8,                                      7)
	TAGKEYS(                        XK_9,                                      8)

	{ MODKEY|ShiftMask,             XK_r,              quit,                   {1} },	/* Restart dwm	requires: dwm-6.1-restart.diff   ( hand patched ) */
	{ MODKEY|ShiftMask,             XK_q,              quit,                   {0} },	/* Cleanly exit dwm */
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

