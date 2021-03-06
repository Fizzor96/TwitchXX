//
// Created by buran on 23/02/18.
//

#ifndef TWITCHXX_STREAM_H
#define TWITCHXX_STREAM_H

#include <string>
#include <StreamType.h>
#include <StreamsOptions.h>
#include <TwitchDef.h>

namespace TwitchXX
{
    class Api;

    /**
    * Stream descriptor
    */
    class Stream
    {
    public:
        unsigned long long       Id;            ///< Stream Id
        unsigned long long       UserId;        ///< User's Id
        unsigned long long       GameId;        ///< Game Id
        std::vector<std::string> CommunityIds;  ///< Community Id
        std::string              Title;         ///< Stream's title
        StreamType::Value        Type;          ///< Stream type
        unsigned long long       Viewers;       ///< Number of viewers
        Date                     Started;       ///< Start time point
        std::string              Language;      ///< Stream languages (defined by sreamer)
        std::string              Thumb;         ///< Stream's thumb URL
    };

    /**
    * Fetch Stream objects. Forward-only request
    * @param api - API object
    * @param count - count of objects per batch (Maximum: 100)
    * @param cursor - forward ('after') cursor. Optional
    * @return a tuple with vector of Strem objects and a cursor
    * @throw TwitchXX::TwitchException in case of count is > 100;
    */
    std::tuple<std::vector<Stream>, std::string> getStreams(const Api &api,
                                                            size_t count,
                                                            const char *cursor = nullptr);

    /**
    * Fetch Stream objects. More complex way of request.
    * @param api - API object
    * @param opt - request options. See GetStreamsOptions for details.
    * @return a tuple with vector of Stream objects and a cursor
    * @throw TwitchXX::TwitchException in case some of the parameters are incorrect.
    */
    std::tuple<std::vector<Stream>, std::string> getStreams(const Api &api,
                                                            const StreamsOptions &opt);
}


#endif //TWITCHXX_STREAM_H
