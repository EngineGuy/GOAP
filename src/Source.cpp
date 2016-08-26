#	include "GOAP/Source.h"

#	include "GOAP/Task.h"
#	include "GOAP/Chain.h"

#	include "GOAP/FunctionProvider.h"
#	include "GOAP/TaskFunction.h"
#	include "GOAP/TaskCallback.h"

#	include "TranscriptorBase.h"
#	include "TranscriptorParallel.h"
#	include "TranscriptorRace.h"


namespace GOAP
{
	//////////////////////////////////////////////////////////////////////////
	Source::Source()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	Source::~Source()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void Source::addTask( const TaskPtr & _task )
	{
		TranscriptorBase * description = new TranscriptorBase( _task );

		m_descriptions.push_back( description );
	}
	//////////////////////////////////////////////////////////////////////////
	TVectorSources & Source::addParallel( size_t _count )
	{
		TranscriptorParallel * description = new TranscriptorParallel( _count );

		m_descriptions.push_back( description );

		TVectorSources & sources = description->getSources();

		return sources;
	}
	//////////////////////////////////////////////////////////////////////////
	TVectorSources & Source::addRace( size_t _count )
	{
		TranscriptorRace * description = new TranscriptorRace( _count );

		m_descriptions.push_back( description );

		TVectorSources & sources = description->getSources();

		return sources;
	}
	//////////////////////////////////////////////////////////////////////////
	void Source::addFunctionProvider( const FunctionProviderPtr & _provider )
	{
		TaskPtr task = new TaskFunction( _provider );

		this->addTask( task );
	}
	//////////////////////////////////////////////////////////////////////////
	void Source::addCallbackProvider( const CallbackProviderPtr & _provider )
	{
		TaskPtr task = new TaskCallback( _provider );

		this->addTask( task );
	}
	//////////////////////////////////////////////////////////////////////////
	TaskPtr Source::parse( const TaskChainPtr & _chain, const TaskPtr & _task )
	{
		TaskPtr current_task = _task;

		for( TVectorDescriptions::iterator
			it = m_descriptions.begin(),
			it_end = m_descriptions.end();
		it != it_end;
		++it )
		{
			const TaskDescriptionPtr & description = *it;

			TaskPtr last_task = description->generate( _chain, current_task );

			current_task = last_task;
		}

		return current_task;
	}

}