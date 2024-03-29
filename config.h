/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int statusbar = 5;        /* 修改状态栏的宽度 */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
                                          "Monaco:size=15:style=Regular",
                                          "Symbols Nerd Font:pixelsize=17:type=2048-em:antialias=true:autohint=true",
                                          "WenQuanYi Zen Hei Mono:size=15:style=Regular:antialias=true:autohint=true"
                                      };
static const char dmenufont[]       = "Monaco:size=15:style=Regular";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_white[]       = "#ffffff";
static const char col_black[]       = "#000000";

static const char col_purp1[]       = "#1d1f21";
static const char col_cyan[]        = "#005577";

static const unsigned int baralpha = 0xc0;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]      = {
        /*               fg         bg         border   */

        [SchemeNorm] = { col_black, "#333333", col_gray2  },
        [SchemeSel]  = { col_gray4, "#333333", "#42A5F5"  },

};
static const unsigned int alphas[][3]      = {
        /*               fg      bg        border     */
        [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
        [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "ﴥ", "", "", "", "" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class                  instance    title       tags mask     isfloating   monitor */
        { "Gimp",                 NULL,       NULL,       0,            1,           -1 },
        { "Google Chrome",        NULL,       NULL,       1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
        /* symbol     arrange function */
        { ""  ,      tile },    /* first entry is default */
        { "缾" ,      NULL },    /* no layout function means floating behavior */
        { "",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-no-lazy-grab", "-show", "drun", "-modi", "drun", "-theme", "~/.config/rofi/launchers/misc/blurry", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *trayer[]  = { "/home/jc/Scripts/dwm/pallets.sh", NULL };
static const char *i3lock[]  = { "/home/jc/Scripts/dwm/i3lock.sh", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "70x25", NULL };

static Key keys[] = {
        /* modifier                     key             function        argument */
        { MODKEY,                       XK_p,           spawn,          {.v = dmenucmd } },
        { MODKEY|ControlMask,           XK_t,           spawn,          {.v = termcmd  } },
        { MODKEY|ShiftMask,             XK_b,           spawn,          {.v = trayer   } },
        { MODKEY|ShiftMask,             XK_l,           spawn,          {.v = i3lock   } },
        { MODKEY,                       XK_b,           togglebar,      {0} },
        { MODKEY|ShiftMask,             XK_j,           rotatestack,    {.i = +1 } },
        { MODKEY|ShiftMask,             XK_k,           rotatestack,    {.i = -1 } },
        { MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,           incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Return,      zoom,           {0} },
        { MODKEY,                       XK_Tab,         view,           {0} },
        { MODKEY|ShiftMask,             XK_c,           killclient,     {0} },
        { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,           setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,       setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
        { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
        { MODKEY,                       XK_apostrophe,  togglescratch,  {.v = scratchpadcmd } },
        TAGKEYS(                        XK_1,                           0)
        TAGKEYS(                        XK_2,                           1)
        TAGKEYS(                        XK_3,                           2)
        TAGKEYS(                        XK_4,                           3)
        TAGKEYS(                        XK_5,                           4)
        TAGKEYS(                        XK_6,                           5)
        TAGKEYS(                        XK_7,                           6)
        TAGKEYS(                        XK_8,                           7)
        TAGKEYS(                        XK_9,                           8)
        { MODKEY|ShiftMask,             XK_q,           quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

