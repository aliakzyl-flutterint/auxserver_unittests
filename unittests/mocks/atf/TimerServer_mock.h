#ifndef PYR_ATF_TIMER_SERVER_PROCESSOR_MOCK_H
#define PYR_ATF_TIMER_SERVER_PROCESSOR_MOCK_H

#include "commmsgbody.h"
#include "pptime.h"
#include "Ref.h"
#include <gmock/gmock.h>

#define SUPERLONGTIMER_MAX_ONE_CHUNK_TIMER_SECS   21600     // 6 hours = 21600 seconds


namespace Atf
{
	class AtfCommObjectImpl;

	class TimerListener
	{
	public:
		virtual ~TimerListener() {}
		virtual void timerStarted(UINT32 timerHandle, bool isRecurringTimer) = 0;
		virtual void timerStopped(UINT32 timerHandle, INT64 timeUsedInMSec, bool isRecurringTimer, bool isTimerCancelled) = 0;
	};


	class TimerHandler
	{
	public:
		virtual ~TimerHandler() {}
		virtual void onTimer( UINT32 timerHandle, UINT32 msgId, const CommMsgBody& body ) = 0;
	};

	class SingleTimerHandler : public TimerHandler, public TimerListener, public RefCounted
	{
	public:
		SingleTimerHandler() {}
		SingleTimerHandler(std::function<void()> func) {}
	protected:
		~SingleTimerHandler() {}
	public:
		MOCK_METHOD(void, onTimer, (UINT32 timerHandle, UINT32 msgId, const CommMsgBody& body));
		MOCK_METHOD(void, timerStarted, (UINT32 timerHandle, bool isRecurringTimer), (override));
		MOCK_METHOD(void, timerStopped, (UINT32 timerHandle, INT64 timeUsedInMSec, bool isRecurringTimer, bool isTimerCancelled), (override));
	public:
		virtual void onSingleTimer() {}
	};


	class TimerObject  // interface for timer object
	{
	public:
		virtual ~TimerObject() {}

		virtual UINT32 getTimerObjectId() const = 0;
		virtual void setTimerObjectId( UINT32 timerObjectId ) = 0;
		virtual void stopAllTimers() = 0;
		virtual bool processMyTimerMessage( UINT32 commTimerId, UINT32 msgId, CommMsgBody& body ) = 0;
	};


	class Timer
	{
	public:
		virtual ~Timer() {}

		virtual UINT32 startTimer(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec) = 0;
		virtual void restartTimer(UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec) = 0;
		virtual UINT32 startRecurringTimer(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec) = 0;

		virtual UINT32 startTimer(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp = NULL) = 0;
		virtual void restartTimer(UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp = NULL) = 0;
		virtual UINT32 startRecurringTimer(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp = NULL) = 0;

		virtual UINT32 startTimer(INT32 timerIntervalInSec, std::function<void()> timerFunc) = 0;
		virtual UINT32 startRecurringTimer(INT32 timerIntervalInSec, std::function<void()> timerFunc) = 0;

		virtual INT32 getTimeLeftS(UINT32 timerHandle) const = 0;
		virtual INT32 getTimeoutIntervalS(UINT32 timerHandle) const = 0;

		virtual UINT32 startTimerMSec(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec) = 0;
		virtual void restartTimerMSec(UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec) = 0;
		virtual UINT32 startRecurringTimerMSec(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec) = 0;

		virtual UINT32 startTimerMSec(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp = NULL) = 0;
		virtual void restartTimerMSec(UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp = NULL) = 0;
		virtual UINT32 startRecurringTimerMSec(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp = NULL) = 0;

		virtual UINT32 startTimerMSec(SingleTimerHandler* handler, INT32 timerIntervalInMSec) = 0;
		virtual UINT32 startRecurringTimerMSec(SingleTimerHandler* handler, INT32 timerIntervalInMSec) = 0;

		virtual UINT32 startTimerMSec(INT32 timerIntervalInMSec, std::function<void()> timerFunc) = 0;
		virtual UINT32 startRecurringTimerMSec(INT32 timerIntervalInMSec, std::function<void()> timerFunc) = 0;

		virtual INT32 getTimeLeftMSec(UINT32 timerHandle) const = 0;
		virtual INT32 getTimeoutIntervalMSec(UINT32 timerHandle) const = 0;

		virtual void stopTimer(UINT32& timerHandle) = 0;

		virtual bool pauseTimer(UINT32 timerHandle) = 0;
		virtual bool resumeTimer(UINT32 timerHandle) = 0;

		virtual bool isActiveTimer( UINT32 timerHandle ) const = 0;
		virtual bool isTimerPaused( UINT32 timerHandle ) const = 0;
		virtual bool isRecurrenceTimer( UINT32 timerHandle ) const = 0;
	};


	class SuperLongTimer
	{
	public:
		virtual ~SuperLongTimer() {}

		virtual UINT32 startLongTimer( TimerHandler* handler, UINT32 msgId, INT32 timerIntervalSecs ) = 0;
		virtual UINT32 startLongTimer( TimerHandler* handler, UINT32 msgId, INT32 timerIntervalSecs, CommMsgBody& body, TimerListener* listener /*could be null*/) = 0;
		virtual UINT32 startLongTimer( INT32 timerIntervalSecs, std::function<void()> timerFunc ) = 0;

		virtual void stopTimer( UINT32& timerHandle ) = 0;

		virtual INT32 getTimeLeftS( UINT32 timerHandle ) const = 0;
		virtual INT32 getTimeoutIntervalS( UINT32 timerHandle ) const = 0;

		virtual bool isActiveTimer( UINT32 timerHandle ) const = 0;
	};


	class TimerServer : public TimerObject, public Timer
	{
	public:
		TimerServer(AtfCommObjectImpl *obj) {}
		~TimerServer() {}

	public:
		MOCK_METHOD(UINT32, getTimerObjectId, (), (const, override));
		MOCK_METHOD(void, setTimerObjectId, (UINT32 timerObjectId_), (override));
		MOCK_METHOD(UINT32, startTimer, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec), (override));
		MOCK_METHOD(void, restartTimer, (UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec), (override));
		MOCK_METHOD(UINT32, startRecurringTimer, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec), (override));
		
		MOCK_METHOD(UINT32, startTimer_impl, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp));
		MOCK_METHOD(void, restartTimer_impl, (UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp));
		MOCK_METHOD(UINT32, startRecurringTimer_impl, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp));
		UINT32 startTimer(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp = NULL) override
		{
			return startTimer_impl(handler, msgId, timerIntervalInSec, body, tbp);
		}
		void restartTimer(UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp = NULL) override
		{
			return restartTimer_impl(timerHandle, handler, msgId, timerIntervalInSec, body, tbp);
		}
		UINT32 startRecurringTimer(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInSec, CommMsgBody& body, TimerListener *tbp = NULL) override
		{
			return startRecurringTimer_impl(handler, msgId, timerIntervalInSec, body, tbp);
		}
		
		MOCK_METHOD(UINT32, startTimer, (INT32 timerIntervalInSec, std::function<void()> timerFunc), (override));
		MOCK_METHOD(UINT32, startRecurringTimer, (INT32 timerIntervalInSec, std::function<void()> timerFunc), (override));
		MOCK_METHOD(INT32, getTimeLeftS, (UINT32 timerHandle), (const, override));
		MOCK_METHOD(INT32, getTimeoutIntervalS, (UINT32 timerHandle), (const, override));
		MOCK_METHOD(UINT32, startTimerMSec, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec), (override));
		MOCK_METHOD(void, restartTimerMSec, (UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec), (override));
		MOCK_METHOD(UINT32, startRecurringTimerMSec, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec), (override));

		MOCK_METHOD(UINT32, startTimerMSec_impl, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp));
		MOCK_METHOD(void, restartTimerMSec_impl, (UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp));
		MOCK_METHOD(UINT32, startRecurringTimerMSec_impl, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp));
		UINT32 startTimerMSec(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp = NULL) override
		{
			return startTimerMSec_impl(handler, msgId, timerIntervalInMSec, body, tbp);
		}
		void restartTimerMSec(UINT32& timerHandle, TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp = NULL) override
		{
			return restartTimerMSec_impl(timerHandle, handler, msgId, timerIntervalInMSec, body, tbp);
		}
		UINT32 startRecurringTimerMSec(TimerHandler* handler, UINT32 msgId, INT32 timerIntervalInMSec, CommMsgBody& body, TimerListener *tbp = NULL) override
		{
			return startRecurringTimerMSec_impl(handler, msgId, timerIntervalInMSec, body, tbp);
		}

		MOCK_METHOD(UINT32, startTimerMSec, (SingleTimerHandler* handler, INT32 timerIntervalInMSec), (override));
		MOCK_METHOD(UINT32, startRecurringTimerMSec, (SingleTimerHandler* handler, INT32 timerIntervalInMSec), (override));

		MOCK_METHOD(UINT32, startTimerMSec, (INT32 timerIntervalInMSec, std::function<void()> timerFunc), (override));
		MOCK_METHOD(UINT32, startRecurringTimerMSec, (INT32 timerIntervalInMSec, std::function<void()> timerFunc), (override));

		MOCK_METHOD(INT32, getTimeLeftMSec, (UINT32 timerHandle), (const, override));
		MOCK_METHOD(INT32, getTimeoutIntervalMSec, (UINT32 timerHandle), (const, override));

		MOCK_METHOD(void, stopTimer, (UINT32& timerHandle), (override));
		MOCK_METHOD(void, stopAllTimers, (), (override));

		MOCK_METHOD(bool, pauseTimer, (UINT32 timerHandle), (override));
		MOCK_METHOD(bool, resumeTimer, (UINT32 timerHandle), (override));

		MOCK_METHOD(bool, isActiveTimer, (UINT32 timerHandle), (const, override));
		MOCK_METHOD(bool, isTimerPaused, (UINT32 timerHandle), (const, override));
		MOCK_METHOD(bool, isRecurrenceTimer, (UINT32 timerHandle), (const, override));

		MOCK_METHOD(bool, processMyTimerMessage, (UINT32 commTimerId, UINT32 msgId, CommMsgBody& body), (override));
	};


	class SuperLongTimerServer : public TimerObject, public SuperLongTimer
	{
	public:
		SuperLongTimerServer(AtfCommObjectImpl* obj) {}
		~SuperLongTimerServer() {}

	public:
		MOCK_METHOD(UINT32, getTimerObjectId, (), (const, override));
		MOCK_METHOD(void, setTimerObjectId, (UINT32 timerObjectId_), (override));

		MOCK_METHOD(UINT32, startLongTimer, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalSecs), (override));
		MOCK_METHOD(UINT32, startLongTimer, (TimerHandler* handler, UINT32 msgId, INT32 timerIntervalSecs, CommMsgBody& body, TimerListener* listener), (override));
		MOCK_METHOD(UINT32, startLongTimer, (INT32 timerIntervalSecs, std::function<void()> timerFunc), (override));

		MOCK_METHOD(INT32, getTimeLeftS, (UINT32 timerHandle), (const, override));
		MOCK_METHOD(INT32, getTimeoutIntervalS, (UINT32 timerHandle), (const, override));
		MOCK_METHOD(void, stopTimer, (UINT32& timerHandle), (override));
		MOCK_METHOD(bool, isActiveTimer, (UINT32 timerHandle), (const, override));

		MOCK_METHOD(void, stopAllTimers, (), (override));
		MOCK_METHOD(bool, processMyTimerMessage, (UINT32 commTimerId, UINT32 msgId, CommMsgBody& body), (override));
	};
};

#endif

