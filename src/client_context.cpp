//
// Copyright (C) 2018 Codership Oy <info@codership.com>
//

#include "client_context.hpp"
#include "transaction_context.hpp"
#include "compiler.hpp"

#include <sstream>
#include <iostream>


trrep::provider& trrep::client_context::provider() const
{
    return server_context_.provider();
}

int trrep::client_context::before_command()
{
    trrep::unique_lock<trrep::mutex> lock(mutex_);
    assert(state_ == s_idle);
    if (server_context_.rollback_mode() == trrep::server_context::rm_sync)
    {

        /*!
         * \todo Wait until the possible synchronous rollback
         * has been finished.
         */
        trrep::unique_lock<trrep::mutex> lock(mutex_);
        while (transaction_.state() == trrep::transaction_context::s_aborting)
        {
            // cond_.wait(lock);
        }
    }
    state(lock, s_exec);
    if (transaction_.state() == trrep::transaction_context::s_must_abort)
    {
        return 1;
    }
    return 0;
}

int trrep::client_context::after_command()
{
    int ret(0);
    trrep::unique_lock<trrep::mutex> lock(mutex_);
    if (transaction_.state() == trrep::transaction_context::s_must_abort)
    {
        lock.unlock();
        rollback(transaction_);
        lock.lock();
        ret = 1;
    }
    state(lock, s_idle);
    return ret;
}

int trrep::client_context::before_statement()
{
#if 0
    /*!
     * \todo It might be beneficial to implement timed wait for
     *       server synced state.
     */
    if (allow_dirty_reads_ == false &&
        server_context_.state() != trrep::server_context::s_synced)
    {
        return 1;
    }
#endif // 0
    return 0;
}

int trrep::client_context::after_statement()
{
#if 0
    /*!
     * \todo Check for replay state, do rollback if requested.
     */
#endif // 0
    transaction_.after_statement();
    return 0;
}

// Private

void trrep::client_context::state(
    trrep::unique_lock<trrep::mutex>& lock TRREP_UNUSED,
    enum trrep::client_context::state state)
{
    assert(lock.owns_lock());
    char allowed[state_max_][state_max_] =
        {
            /* idle exec quit */
            {  0,   1,   1}, /* idle */
            {  1,   0,   1}, /* exec */
            {  0,   0,   0}
        };
    if (allowed[state_][state])
    {
        state_ = state;
    }
    else
    {
        std::ostringstream os;
        os << "client_context: Unallowed state transition: "
           << state_ << " -> " << state << "\n";
        throw trrep::runtime_error(os.str());
    }
}
