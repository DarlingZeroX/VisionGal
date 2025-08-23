﻿#pragma once
#include "../imconfig.h"
#include "ImTaskInterface.h"
#include <stdint.h>
#include <HCore/Include/HConfig.h>
#include <HCore/Include/Core/HSingleton.h>

namespace ImGuiEx {

    // creation flags
    enum class ImTaskFlags : std::uint32_t
    {
        None = 0,
        ShowInUI = (1 << 0),
        UseThreadPool = (1 << 1),                     // this will spawn the task using a limited pool of threads (with somewhere between 'cores-1' and 'logical threads-1' thread count) which means the thread might have to wait before it will start running so be careful not to cause deadlocks with any internal dependencies 
    };

	class IMGUI_API ImTaskManager: public Horizon::HSingletonBase<ImTaskManager>
	{
        struct TaskInternal : ImTaskInterface::Task
        {
            ImTaskInterface::TaskContext             Context;

            const ImTaskFlags        Flags;                              // is it visible in UI? (InsertImGuiWindow/InsertImGuiContent)

            Scope<ImTaskInterface>  TaskInstance;                               // the actual task

            TaskInternal(const std::string& name, ImTaskFlags flags, ImTaskInterface* task) : Task(name), Flags(flags), TaskInstance(task) { }

            TaskInternal(const TaskInternal&) = delete;
            TaskInternal& operator =(const TaskInternal&) = delete;
        };

		std::list<Ref<TaskInternal>>       m_currentUITasks;

	private:
        ImTaskManager() = default;
	public:
		~ImTaskManager() override = default;

		static void CreateManager();

        Ref<ImTaskInterface::Task> NewTask(ImTaskInterface* task, const std::string& taskName, ImTaskFlags flags = ImTaskFlags::None);

        void RenderUITask();

        virtual void FrameUpdate();

        virtual void FixedUpdate();
	};

    IMGUI_API Ref<ImTaskInterface::Task> NewUITask(ImTaskInterface* task, const std::string& taskName, ImTaskFlags flags = ImTaskFlags::None);

}
