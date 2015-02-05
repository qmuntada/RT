# RT

Projet vierge : voir le Rtv1.

note a moi-meme :

//Comment realiser l'effet "vignette"
col = vecopx(&col, 0.2 + 0.8 * pow(16.0 * (double)x / e->screen.width * (double)y / e->screen.height * (1.0 - (double)x / e->screen.width ) * (1.0 - (double)y / e->screen.height ), 0.15));

