﻿#include "VideosTest.h"
#include "TwitchVideo.h"


TEST_F(VideosTest, GetVideo)
{
	TwitchXX::TwitchVideo video;

	ASSERT_NO_THROW(
	{
		video = _api->GetVideo(87775038U);
	});

	EXPECT_EQ(video.ChannelName.Get(), U("waveafterwave2ndlife"));
}

TEST_F(VideosTest, GetTopVideos)
{
	TwitchXX::TwitchVideosContainer result;

	ASSERT_NO_THROW(
	{
		result = _api->GetTopVideo(U("Dota 2"),U(""));
	});

	EXPECT_GT(result.size(), 1U);
}

TEST_F(VideosTest, GetFollowedVideos)
{
	TwitchXX::TwitchVideosContainer result;

	ASSERT_NO_THROW(
	{
		result = _api->GetFollowedVideo(U(""));
	});

	EXPECT_GT(result.size(), 1U);
}