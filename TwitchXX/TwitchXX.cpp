#include <fstream>
#include "TwitchXX.h"
#include "TwitchGames.h"
#include "TwitchStreams.h"
#include "TwitchChannels.h"
#include "TwitchChannelFeed.h"
#include "TwitchChat.h"

namespace TwitchXX
{
	class TwitchStreams;
	std::shared_ptr<std::map<std::wstring,std::wstring>> Options = std::make_shared<std::map<std::wstring, std::wstring>>();
	std::string DatabaseName = "TwitchSpy";
	std::shared_ptr<Logger> Log = std::make_shared<Logger>();
	extern void trim(std::wstring& s);
}

std::map<TwitchXX::Api::Version,std::wstring> TwitchXX::Api::_version =
{
	{ Version::v2, L"application/vnd.twitchtv.v2+json" },
	{ Version::v3, L"application/vnd.twitchtv.v3+json" }
};

TwitchXX::Api::Api(const std::wstring& client_id, Version version, std::shared_ptr<Logger> log)
{
	//reading options
	std::wifstream options_file("twitchxx.cfg");
	std::wstring line;
	while(std::getline(options_file,line))
	{
		std::wstringstream iss(line);
		std::wstring name, value;
		std::getline(iss, name, L'=');
		std::getline(iss, value);
		trim(name);
		trim(value);

		Options->insert(std::make_pair(name, value));
	}
	if (client_id.size() && Options->find(U("api_key")) != Options->end())
	{
		//Do not override config file's api_key parameter event if explicitly provided by parameter
		Options->insert(std::make_pair(U("api_key"), client_id));
	}
	Options->insert(std::make_pair(U("version"), _version[version]));

	_streams = std::make_unique<TwitchStreams>();
	_channels = std::make_unique<TwitchChannels>();
	_channel_feed = std::make_unique<TwitchChannelFeed>();
	_chat = std::make_unique<TwitchChat>();

	if(log != nullptr)
	{
		Log->Subscribe(log);
	}
	Log->Log(U("Api created"));
}


TwitchXX::Api::~Api()
{
	Log->Log(U("Api destroyed"));
}

void TwitchXX::Api::AddLogger(std::shared_ptr<Logger>log)
{
	if(log != nullptr)
	{
		Log->Subscribe(log);
	}
}

TwitchXX::TwitchGamesVector TwitchXX::Api::TopGames(size_t top_count)
{
	TwitchGames games(100);
	return games.GetTopGames(top_count);
}

TwitchXX::TwitchStream TwitchXX::Api::GetStream(const std::wstring& name) const
{
	return  _streams->GetStream(name);
}

TwitchXX::TwitchStreamsVector TwitchXX::Api::TopStreams(size_t top_count, const options& op) const
{
	try
	{
		return _streams->GetStreams(top_count, op);
	}
	catch(std::runtime_error& e)
	{
		std::wcout << e.what() << "\n";
	}

	return TwitchStreamsVector();

}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::Api::GetFeaturedStreams() const
{
	return _streams->GetFeaturedStreams();
}

std::tuple<size_t, size_t> TwitchXX::Api::GetSummary(const std::wstring& game) const
{
	return _streams->GetSummary(game);
}

TwitchXX::TwitchStreamsContainer TwitchXX::Api::FollowedStreams() const
{
	return _streams->GetFollowedStreams();
}

TwitchXX::TwitchChannel TwitchXX::Api::GetChannel(const std::wstring & name) const
{
	return _channels->GetChannel(name);
}

TwitchXX::TwitchUsersContainer TwitchXX::Api::GetChannelEditors(const std::wstring& channel_name) const
{
	return _channels->GetChannelEditors(channel_name);
}

TwitchXX::TwitchChannel TwitchXX::Api::UpdateChannel(const std::wstring& channel_name, const TwitchXX::options& op) const
{
	return _channels->UpdateChannel(channel_name, op);
}

std::wstring TwitchXX::Api::ResetStreamKey(const std::wstring& channel_name) const
{
	return _channels->ResetStreamKey(channel_name);
}

bool TwitchXX::Api::StartCommercial(const std::wstring& channel_name, size_t length) const
{
	return _channels->StartCommercial(channel_name, length);
}

TwitchXX::TwitchTeamsContainer TwitchXX::Api::GetTeams(const std::wstring& channel_name) const
{
	return _channels->GetTeams(channel_name);
}

TwitchXX::TwitchPostsContainer TwitchXX::Api::GetPosts(const std::wstring& channel_name, size_t count) const
{
	return _channel_feed->GetPosts(channel_name, count);
}

TwitchXX::TwitchPost TwitchXX::Api::GetPost(const std::wstring& channel_name, unsigned long long id) const
{
	return _channel_feed->GetPost(channel_name, id);
}

TwitchXX::TwitchPost TwitchXX::Api::Post(const std::wstring& channel_name, const std::wstring& body, bool share) const
{
	return _channel_feed->Post(channel_name, body, share);
}

bool TwitchXX::Api::DeletePost(const std::wstring & channel_name, unsigned long long id) const
{
	return _channel_feed->DeletePost(channel_name, id);
}

bool TwitchXX::Api::AddReaction(const std::wstring & channel_name, unsigned long long id, size_t emote_id) const
{
	return _channel_feed->AddReaction(channel_name, id, emote_id);
}

bool TwitchXX::Api::RemoveReaction(const std::wstring & channel_name, unsigned long long id, size_t emote_id) const
{
	return _channel_feed->RemoveReaction(channel_name, id, emote_id);
}

TwitchXX::TwitchEmoticonsContainer TwitchXX::Api::GetEmoticons() const
{
	return _chat->GetEmoticons();
}

std::set<TwitchXX::EmoticonImage> TwitchXX::Api::GetEmoticoneImages(std::set<size_t> sets) const
{
	return _chat->GetEmoticoneImages(sets);
}

std::set<TwitchXX::ChannelBadge> TwitchXX::Api::GetChannelBadges(std::wstring& channel_name) const
{
	return _chat->GetChannelBadges(channel_name);
}
