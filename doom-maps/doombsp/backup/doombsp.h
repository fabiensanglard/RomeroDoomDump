// doombsp.h

#import <appkit/appkit.h>
#import <math.h>
#import "cmdlib.h"
#import "idfunctions.h"
#import "Wadfile.h"
#include "DoomData.h"

#define	SHORT(x)	NXSwapLittleShortToHost((short)x)
#define	LONG(x)		NXSwapLittleLongToHost((short)x)

#define PI	3.141592657

/*
===============================================================================

							map file types

===============================================================================
*/

typedef struct
{
	int			floorheight, ceilingheight;
	char 		floorflat[9], ceilingflat[9];
	int			lightlevel;
	int			special, tag;	
} sectordef_t;

typedef struct
{
	int			firstrow;	
	int			firstcollumn;
	char		toptexture[9];
	char		bottomtexture[9];
	char		midtexture[9];
	sectordef_t	sectordef;			// on the viewer's side
	int			sector;				// only used when saving doom map
} worldside_t;

typedef struct
{
	NXPoint		p1, p2;
	int			special, tag;
	int			flags;	
	worldside_t	side[2];
} worldline_t;

#define	ML_BLOCKMOVE	1
#define	ML_TWOSIDED		4	// backside will not be present at all if not two sided

typedef struct
{
	NXPoint		origin;
	int			angle;
	int			type;
	int			options;
	int			area;
} worldthing_t;

/*
===============================================================================

							internal types

===============================================================================
*/

typedef	struct
{
	NXPoint	pt;
	float	dx,dy;
}divline_t;

typedef struct bspstruct_s
{
	id						lines_i;		// if non NULL, the node is
	divline_t				divline;		// terminal and has no children
	float					bbox[4];
	struct	bspstruct_s		*side[2];
} bspnode_t;


typedef struct
{
	NXPoint		p1, p2;
	int			linedef, side, offset;
	boolean		grouped;				// internal error check
} line_t;


/*
===============================================================================

								doombsp

===============================================================================
*/

extern	id			wad_i;
extern	boolean		draw;


/*
===============================================================================

								doomload

===============================================================================
*/

extern	id	linestore_i, thingstore_i;

void LoadDoomMap (char *mapname);


/*
===============================================================================

								drawing

===============================================================================
*/

extern	id 	window_i, view_i;
extern	float	scale;
extern	NXRect		worldbounds;

void EraseWindow (void);
void DrawMap (void);
void DrawLineStore (id lines_i);
void DrawDivLine (divline_t *div);
void DrawLineDef (maplinedef_t *ld);


/*
===============================================================================

								buildbsp

===============================================================================
*/

extern	int		cuts;			// number of new lines generated by BSP process
extern	bspnode_t	*startnode;

void BuildBSP (void);
void	DivlineFromWorldline (divline_t *d, line_t *w);
int	PointOnSide (NXPoint *p, divline_t *l);



/*
===============================================================================

							savebsp

===============================================================================
*/

extern	id		secstore_i;
extern	id		mapvertexstore_i;
extern	id		subsecstore_i;
extern	id		maplinestore_i;
extern	id		nodestore_i;
extern	id		mapthingstore_i;
extern	id		ldefstore_i;
extern	id		sdefstore_i;

void SaveDoomMap (void);

/*
===============================================================================

							saveblocks

===============================================================================
*/

void SaveBlocks (void);

/*
===============================================================================

							savesectors

===============================================================================
*/

void ProcessSectors (void);
void BuildSectordefs (void);

/*
===============================================================================

							saveconnect

===============================================================================
*/

void ProcessConnections (void);

