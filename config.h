/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static int swallowfloating          = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=10";

/* colorscheme */
/* background */
static const char normbgcolor[]           = "#222222";
/* inactive window border */
static const char normbordercolor[]       = "#444444";
/* font color */
static const char normfgcolor[]           = "#bbbbbb";
/* selected tag and window font */
static const char selfgcolor[]            = "#eeeeee";
/* bar color */
static const char selbgcolor[]            = "#990044";
/* active window border */
static const char selbordercolor[]        = "#757575";
static const char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance       title       	    tags mask    isfloating   isterminal   noswallow   monitor */
	{ "Gimp",     NULL,        NULL,       	    0,           1,           0,           0,          -1 },
	{ NULL,       "Navigator", NULL,            1 << 2,      0,           0,           0,          -1 },
	{ "discord",  NULL,        NULL,            1 << 3,      0,           0,           0,          -1 },
	{ NULL,       NULL,        "rover",         1 << 6,      0,           0,           0,          -1 },
	{ "Zathura",  NULL,        NULL,            1 << 7,      0,           0,           0,          -1 },
	{ NULL,       NULL,        "htop",          1 << 8,      0,           0,           0,          -1 },
	{ "St",       NULL,        "st",            1 << 1,      0,           1,           0,          -1 },
	{ NULL,       NULL,        "Event Tester",  0,           0,           0,           1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* #include "vanitygaps.c" */

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SPAWN(...) {.v = (const char*[]){ __VA_ARGS__, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char terminal[]  = "st"; /* preferred terminal emulator */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { terminal, NULL };
static const char *passcmd[]  = { "passmenu", NULL };

static Key keys[] = {
	/* modifier         key           function        argument */
	{ MODKEY,           XK_d,         spawn,          {.v = dmenucmd } },
	{ MODKEY,           XK_p,         spawn,          {.v = passcmd } },
	{ MODKEY,           XK_Return,    spawn,          {.v = termcmd } },
	{ MODKEY,           XK_b,         togglebar,      {0} },
	{ MODKEY,           XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,           XK_Up,        incnmaster,     {.i = +1 } },
	{ MODKEY,           XK_Down,      incnmaster,     {.i = -1 } },
	{ MODKEY,           XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_space,     zoom,           {0} },
	{ MODKEY|ShiftMask, XK_space,     togglefloating, {0} },
	{ MODKEY,           XK_Tab,       view,           {0} },
	{ MODKEY,           XK_q,         killclient,     {0} },
	{ MODKEY,           XK_y,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_u,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_i,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,           XK_o,         setlayout,      {0} },
	{ MODKEY,           XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,           XK_Right,     viewnext,       {0} },
	{ MODKEY,           XK_Left,      viewprev,       {0} },
	{ MODKEY|ShiftMask, XK_Right,     tagtonext,      {0} },
	{ MODKEY|ShiftMask, XK_Left,      tagtoprev,      {0} },
	TAGKEYS(            XK_1,                         0)
	TAGKEYS(            XK_2,                         1)
	TAGKEYS(            XK_3,                         2)
	TAGKEYS(            XK_4,                         3)
	TAGKEYS(            XK_5,                         4)
	TAGKEYS(            XK_6,                         5)
	TAGKEYS(            XK_7,                         6)
	TAGKEYS(            XK_8,                         7)
	TAGKEYS(            XK_9,                         8)
	{ MODKEY|ShiftMask, XK_q,         quit,           {0} },
	{ MODKEY,           XK_BackSpace, spawn,          {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY,           XK_F1,        spawn,          SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
	{ MODKEY,           XK_F2,        statusbarcmd,   {.v = (const Arg[]){ {.v = (const char*[]){ terminal, "pulsemixer", NULL } }, { .i = 10 }, {.i = 1 } } } },
	{ MODKEY,           XK_comma,     statusbarcmd,   {.v = (const Arg[]){ SPAWN("pamixer", "-d5"), { .i = 10 }, {0} } } },
	{ MODKEY|ShiftMask, XK_comma,     statusbarcmd,   {.v = (const Arg[]){ {.v = (const char*[]){ "pamixer", "-d15", NULL } }, { .i = 10 }, {0} } } },
	{ MODKEY,           XK_period,    statusbarcmd,   {.v = (const Arg[]){ {.v = (const char*[]){ "pamixer", "-i5", NULL } }, { .i = 10 }, {0} } } },
	{ MODKEY|ShiftMask, XK_period,    statusbarcmd,   {.v = (const Arg[]){ {.v = (const char*[]){ "pamixer", "-i15", NULL } }, { .i = 10 }, {0} } } },
	{ MODKEY,           XK_m,         statusbarcmd,   {.v = (const Arg[]){ {.v = (const char*[]){ "pamixer", "-t", NULL } }, { .i = 10 }, {0} } } },
	{ MODKEY,           XK_w,         spawn,          {.v = (const char*[]){ "firefox", NULL } } },
	{ MODKEY,           XK_c,         spawn,          {.v = (const char*[]){ "discord", NULL } } },
	{ MODKEY,           XK_t,         spawn,          {.v = (const char*[]){ terminal, "htop", NULL } } },
	{ MODKEY,           XK_r,         spawn,          {.v = (const char*[]){ terminal, "rover", NULL } } },
	{ MODKEY,           XK_n,         spawn,          {.v = (const char*[]){ terminal, "newsboat", NULL } } },
	{ 0,                XK_Print,     spawn,          SHCMD("maim ~/Pictures/screenshots/full/$(date +%s).png") },
	{ MODKEY,           XK_Print,     spawn,          {.v = (const char*[]){ "maimpick", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        MODKEY,         Button1,        sigstatusbar,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        viewprev,	{0} },
	{ ClkTagBar,            0,              Button5,        viewnext,	{0} },
};
