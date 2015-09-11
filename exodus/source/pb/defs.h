//
// defs.inc
//

void iLoadFile(u32* diskOffset, u32 entry);
void iWriteFloppyFile(u32 entry);
void update_dt(u32 entry);
void update_np(u32 entry);
void update_rp(u32 entry);
void iComputeHeadTrackSectors(u32 entry, u8* sheadp, u8* strackp, u8* ssectorp, u8* eheadp, u8* etrackp, u8* esectorp);
void iComputeHeadTrackSector(u32 offset, u8* headp, u8* trackp, u8* sectorp);
u32 setu32(u32* variable, u32 value);
