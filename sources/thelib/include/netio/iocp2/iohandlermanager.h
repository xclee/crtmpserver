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

#ifdef NET_IOCP2
#ifndef _IOHANDLERMANAGER_H
#define	_IOHANDLERMANAGER_H



#include "utils/core.h"
#include "netio/iocp2/iohandlermanagertoken.h"

class IOHandler;
struct _ConnectOV;

class DLLEXP IOHandlerManager {
private:
    static bool _signalShutdown;
    static HANDLE _iocp;
    static uint32_t _numberOfThreads;
    static map<uint32_t, IOHandler *> _activeIOHandlers;
    static map<uint32_t, IOHandler *> _deadIOHandlers;
    static vector<IOHandlerManagerToken *> _tokensVector1;
    static vector<IOHandlerManagerToken *> _tokensVector2;
    static vector<IOHandlerManagerToken *> *_pAvailableTokens;
    static vector<IOHandlerManagerToken *> *_pRecycledTokens;
    static TimersManager *_pTimersManager;
public:
	static map<uint32_t, IOHandler *> & GetActiveHandlers();
    static map<uint32_t, IOHandler *> & GetDeadHandlers(); 
    static void Initialize();
    static void SignalShutdown();
    static void ShutdownIOHandlers();
    static void Shutdown();
    static void RegisterIOHandler(IOHandler *pIOHandler);
    static void UnRegisterIOHandler(IOHandler *pIOHandler);
    static bool EnableReadData(IOHandler *pIOHandler);
    static bool DisableReadData(IOHandler *pIOHandler, bool ignoreError = false);
    static bool EnableWriteData(IOHandler *pIOHandler);
    static bool DisableWriteData(IOHandler *pIOHandler, bool ignoreError = false);
    static bool EnableAcceptConnections(IOHandler *pIOHandler);
    static bool DisableAcceptConnections(IOHandler *pIOHandler, bool ignoreError = false);
    static bool EnableTimer(IOHandler *pIOHandler, uint32_t seconds);
    static bool DisableTimer(IOHandler *pIOHandler, bool ignoreError = false);
    static bool EnableConnectEvent(IOHandler *pIOHandler, _ConnectOV *pConnectOV);
    static void EnqueueForDelete(IOHandler *pIOHandler);
    static void DeleteDeadHandlers();
    static bool Pulse();
private:
    static void SetupToken(IOHandler *pIOHandler);
    static void FreeToken(IOHandler *pIOHandler);
    static void ProcessTimer(TimerEvent &event);
};


#endif	/* _IOHANDLERMANAGER_H */
#endif /* NET_IOCP2 */

