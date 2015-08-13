#pragma once

#include "io/event/io_request_url_event.h"
#include "io/event/io_notify_new_filesystem_event.h"
#include "io/event/io_notify_replace_filesystem_event.h"
#include "io/event/io_notify_delete_filesystem_event.h"
#include "io/filesystem/filesystem.h"

#include "event/threading_handler.h"

#include <map>

namespace sam
{
    class io_thread : public threading_handler
    {
    public:
        CREATE_FUNC_DECLARE(io_thread)

        io_thread();

        virtual ~io_thread();

    protected:
        virtual void enter_thread() override;

        virtual void leave_thread() override;

        virtual void forward_handle() override;

    private:
        void handle_request_url_event(io_request_url_event_ptr &e);

		void handle_notify_new_filesystem_event(io_notify_new_filesystem_event_ptr &e);

		void handle_notify_replace_filesystem_event(io_notify_replace_filesystem_event_ptr &e);

		void handle_notify_delete_filesystem_event(io_notify_delete_filesystem_event_ptr &e);

    protected:
        std::map<std::string, filesystem_ptr> filesystems;
    };

    typedef std::shared_ptr<io_thread> io_thread_ptr;
}