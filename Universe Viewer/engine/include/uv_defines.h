#define   START printf("WHEREAMI : %s line %d\n", __FILE__, __LINE__)

# define M_El		2.7182818284590452353602874713526625L  /* e */
# define M_LOG2El	1.4426950408889634073599246810018921L  /* log_2 e */
# define M_LOG10El	0.4342944819032518276511289189166051L  /* log_10 e */
# define M_LN2l		0.6931471805599453094172321214581766L  /* log_e 2 */
# define M_LN10l	2.3025850929940456840179914546843642L  /* log_e 10 */
# define M_PIl		3.1415926535897932384626433832795029L  /* pi */
# define M_PI_2l	1.5707963267948966192313216916397514L  /* pi/2 */
# define M_PI_4l	0.7853981633974483096156608458198757L  /* pi/4 */
# define M_1_PIl	0.3183098861837906715377675267450287L  /* 1/pi */
# define M_2_PIl	0.6366197723675813430755350534900574L  /* 2/pi */
# define M_2_SQRTPIl	1.1283791670955125738961589031215452L  /* 2/sqrt(pi) */
# define M_SQRT2l	1.4142135623730950488016887242096981L  /* sqrt(2) */
# define M_SQRT1_2l	0.7071067811865475244008443621048490L  /* 1/sqrt(2) */

#define TITLE "Universe Viewer 2"

#define	NBVIEWS		6
#define	NBGRAPHICS	11
#define	NBPLOTS		4
#define	SCALE		2.05

#ifndef ABS
# define ABS(x)	((x<0)?(-x):(x))
#endif

#define	LAMBDA	1.0
#define	OMEGA	0.2
#define	K	0.20005
#define	ALPHA	0.00005
#define	AGE	12.098586