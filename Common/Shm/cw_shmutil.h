#ifndef CW_SHMUTIL_H
#define CW_SHMUTIL_H

#define SM_FREE	0x00
#define SM_ME_READ 0x01
#define SM_ME_WRITE 0x02
#define SM_OT_READ 0X03
#define SM_OT_WRITE 0X04

void	sm_lock(char& flag, char type);
bool	sm_trylock(char& flag, char type);
void	sm_unlock( char& flag);

#endif