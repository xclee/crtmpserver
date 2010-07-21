/* 
 *  Copyright (c) 2010,
 *  Gavriloaie Eugen-Andrei (shiretu@gmail.com)
 *
 *  This file is part of crtmpserver.
 *  crtmpserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  crtmpserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with crtmpserver.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _BASEOUTSTREAM_H
#define	_BASEOUTSTREAM_H

#include "streaming/basestream.h"

class BaseInStream;

class DLLEXP BaseOutStream
: public BaseStream {
private:
	bool _canCallDetachedFromInStream;
protected:
	BaseInStream *_pInStream;
public:
	BaseOutStream(BaseProtocol *pProtocol, StreamsManager *pStreamsManager,
			uint64_t type, string name);
	virtual ~BaseOutStream();

	/*
	 * Returns the stream capabilities. Specifically, codec and codec related info
	 * */
	virtual StreamCapabilities * GetCapabilities();

	/*
	 * The networking layer signaled the availability for sending data
	 * */
	virtual void ReadyForSend();

	/*
	 * pInStream - the in-stream where we want to attach
	 * reverseLink - if true, pInStream::Link will be called internally
	 *               this is used to break the infinite calls.
	 * */
	virtual bool Link(BaseInStream *pInStream, bool reverseLink = true);

	/*
	 * reverseUnLink - if true, pInStream::UnLink will be called internally
	 *               this is used to break the infinite calls
	 * */
	virtual bool UnLink(bool reverseUnLink = true);

	/*
	 * Returns true if this stream is linked to an inbound stream. Otherwise
	 * returns false
	 * */
	bool IsLinked();

	/*
	 * Returns the feder of this stream
	 * */
	BaseInStream *GetInStream();

	/*
	 * This will start the feeding process
	 * absoluteTimestamp - the timestamp where we want to seek
	 *                     before start the feeding process
	 * */
	virtual bool Play(double absoluteTimestamp, double length);

	/*
	 * This will pause the feeding process
	 * */
	virtual bool Pause();

	/*
	 * This will resume the feeding process
	 * */
	virtual bool Resume();

	/*
	 * This will seek to the specified point in time.
	 * */
	virtual bool Seek(double absoluteTimestamp);

	/*
	 * This will stop the feeding process
	 * */
	virtual bool Stop();

	/*
	 * Called after the link is complete
	 * */
	virtual void SignalAttachedToInStream() = 0;

	/*
	 * Called after the link is broken
	 * */
	virtual void SignalDetachedFromInStream() = 0;

	/*
	 * Called when the feeder finished the work
	 * */
	virtual void SignalStreamCompleted() = 0;
};

#endif	/* _BASEOUTBOUNDSTREAM_H */
