// vpacket.h
//  SINS distributed under the GPL

// Orig Author - Maerlyn (MaerlynTheWiz@yahoo.com)
// Date - 3/11/00

// VPacket
// VPacket is a generic class that allows recording and playback of
// generic data with timestamps.  The data is stored in binary format
// with headers around it so that it is retrieved in the same manner
// (exact same 'chunks') that it was sent.  This makes a good class for
// a packet capture
//
// The following public member functions are available:
//
// playback(...)		Fetch data from the buffer
// record(...)			Record data to the buffer
// flush()				Force a flush of data to the file
// setPlaybackSpeed()	Set a playback rate (0=not timed, 1=1X, etc)
// playbackSpeed()		Get the playback rate
// endOfData()			Check for out of data
//
// The intention of this class was to capture network packets to play back
// at a later time.  Using without a file is untested, as well as using to
// playback and record simultaneously.

#ifndef VPACKET_H
#define VPACKET_H

#include <time.h>

#define DEFBUFSIZE 8192
#define USEVERSION

struct packet_struct
{
	long		size;
	time_t		time;
#ifdef USEVERSION
	long		version;
#endif
	long		ms;
	long		sequence;
	char		buffer[ 0 ];
};

class VPacket
{
public:
	VPacket( const char* name = NULL, long timed = 3, bool bRecord = false,
		long bufsize = DEFBUFSIZE );

	~VPacket();

	long playback( char* buff, long bufsize, time_t* time, long* ver = NULL );
	long record( const char* buff, long bufsize, time_t time, long ver = 0 );
	void Flush() { writeBuffer(); }
	void setPlaybackSpeed( long speed );
	void setFlushPacket( bool inset ) { m_bFlushPacket = inset; }
	void setCompressTime( long ms ) { m_nCompressTime = ms; }
	long playbackSpeed() { return m_nPlaybackSpeed; }
	bool endOfData() { return m_bEndofFile; }
	long filePos() { return m_lBytesIO;   }

protected:
	long fillBuffer();
	long writeBuffer();
	long flush();
	long mTime();

	char*		m_sFile;
	long		m_fd;

	char*		m_cBuffer;
	long		m_nBufIndex;           // Current Index into buffer
	long		m_nBufBytes;           // Bytes avail in buffer
	long		m_nBufSize;            // Max Size of buffer
	long		m_nPlaybackSpeed;      // Playback speed (0=ASAP, 1=1x, 2=2x, etc)
	long		m_lStartTime;
	long		m_nSequence;
	bool		m_bEndofFile;
	long		m_lBytesIO;            // number of bytes transferred since creation

	bool		m_bFlushPacket;
	long		m_nLastPacketTime;
	long		m_nFirstPacketTime;
	long		m_nLastTime;
	long		m_nCompressTime;
};

#endif
