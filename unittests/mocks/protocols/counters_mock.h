#ifndef include_counters_mock_h
#define include_counters_mock_h

#ifdef _DEBUG
	#include "pperror.h"
#endif
#include "HeLogger.h"
#include "commmsgbody.h"
#include <gmock/gmock.h>

class HiresCounter
{
public:
	HiresCounter()
	{
	}
	MOCK_METHOD(void, start, ()); 
	MOCK_METHOD(void, stop, ());
	MOCK_METHOD(INT32, getElapsed32, (), (const));
	MOCK_METHOD(UINT32, getElapsedTick, (), (const));
    MOCK_METHOD(void, compose, (CommMsgBody& body), (const));
    MOCK_METHOD(void, parse, (CommMsgParser& parser));
};

class TicksAccumulator
{
public:
	MOCK_METHOD(void, addMessageTicks_impl, (const HiresCounter& counter, bool countMessage));
	void addMessageTicks(const HiresCounter& counter, bool countMessage = true)
	{
		return addMessageTicks_impl(counter, countMessage);
	}
	MOCK_METHOD(void, countMessage, ());
	MOCK_METHOD(void, reset, ());
	MOCK_METHOD(void, stop, ());
	TicksAccumulator() { }
	MOCK_METHOD(INT64, getAccumulated, (), (const));
	MOCK_METHOD(INT32, getAccumulated32, (), (const));
	MOCK_METHOD(INT32, getAccumulatedTicks, (), (const));
	MOCK_METHOD(UINT32, getMessagesProcessed, (), (const));
	MOCK_METHOD(UINT32, messagesPerSec, (), (const));
	MOCK_METHOD(double, messagesPerSecF, (), (const));
	MOCK_METHOD(UINT32, avgProcessingMkSec, (), (const));
	MOCK_METHOD(double, avgProcessingMkSecF, (), (const));
	MOCK_METHOD(UINT32, avgProcessingMkSecTick, (), (const));
	MOCK_METHOD(UINT32, loadPercentCnt, (), (const));
	MOCK_METHOD(double, loadPercentCntF, (), (const));
	MOCK_METHOD(UINT32, loadPercentCntTick, (), (const));
	MOCK_METHOD(UINT32, mSecondsElapsed, (), (const));
	MOCK_METHOD(UINT64, getCounterElapsed, (), (const));
};

class TicksAccumulatorStopResetWrapper
{
public:
	TicksAccumulatorStopResetWrapper(TicksAccumulator& ticksAccumulator_) {}
	~TicksAccumulatorStopResetWrapper() {}

public:
	MOCK_METHOD(void, reportTicks, (const char* nameSuffix, const HeLogger* heLogger, CommMsgBody& reportBody), (const));
};

class TicksAccumulatorAddCounterWrapper
{
public:
	TicksAccumulatorAddCounterWrapper(TicksAccumulator& ticksAccumulator_) {}
	~TicksAccumulatorAddCounterWrapper() {}
};

class QueueAccumulator
{
	UINT32 n, total, hwm;

public:
	QueueAccumulator() { reset(); }
	void reset() { n = total = hwm = 0; }
	void addQueue( UINT32 sz )
	{
		n++;
		total += sz;
		if( sz > hwm )
			hwm = sz;
	}
	UINT32 getAverage() const { return n ? ( total / n ) : 0; }
	double getAverageF() const { return n ? ( double(total) / n ) : 0.0; }
	UINT32 getMax() const { return hwm; }
	UINT32 getCount() const { return n; }
	UINT32 getTotal() const { return total; }
};

class MessageMonitor;
class StepMonitor;

class MonitorForMessages
{

public:
	MonitorForMessages()
	{
	}
	
	MonitorForMessages(const MonitorForMessages& other) = delete;
	MonitorForMessages& operator=(const MonitorForMessages& other) = delete;

	MOCK_METHOD(void, registerMonitor, (const UINT32 msgId, const char* name));
	MOCK_METHOD(void, startMonitor, (const UINT32 msgId, MessageMonitor& msgMonitor));
	MOCK_METHOD(void, startStep, (const char* name, StepMonitor& stepMonitor));
	MOCK_METHOD(void, reportPerformance, (const HeLogger* helogger, CommMsgBody& reportBody));
};

class MessageMonitor
{
public:
	MessageMonitor() {}

	MessageMonitor(const MessageMonitor& other) = delete;
	MessageMonitor& operator=(const MessageMonitor& other) = delete;

	MOCK_METHOD(void, stop, ());
	MOCK_METHOD(void, reset, ());

	~MessageMonitor() {}
};

class StepMonitor
{
public:
	StepMonitor() {}

	StepMonitor(const StepMonitor& other) = delete;
	StepMonitor& operator=(const StepMonitor& other) = delete;

	MOCK_METHOD(void, stop, ());
	MOCK_METHOD(void, reset, ());

	~StepMonitor() {}
};

class RequestDelayMonitor
{
public:
	RequestDelayMonitor() {}

	MOCK_METHOD(void, clear, ());
	MOCK_METHOD(void, requestOut, (UINT32 reqId));
	MOCK_METHOD(void, requestIn, (UINT32 reqId));
	MOCK_METHOD(UINT32, getAveDelay, (), (const));
	MOCK_METHOD(UINT32, getMaxDelay, (), (const));
	MOCK_METHOD(UINT32, getPendingSize, (), (const));
};

#endif //include_counters_mock_h
