/* Copyright (c) 2018 The node-webrtc project authors. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */
#ifndef SRC_RTCRTPSENDER_H_
#define SRC_RTCRTPSENDER_H_

#include <memory>

#include <nan.h>
#include <webrtc/rtc_base/scoped_ref_ptr.h>
#include <v8.h>  // IWYU pragma: keep

#include "src/asyncobjectwrap.h"

namespace webrtc {

class RtpSenderInterface;

}  // namespace webrtc

namespace node_webrtc {

class MediaStreamTrack;
class PeerConnectionFactory;

template <typename K, typename V> class BidiMap;

class RTCRtpSender: public node_webrtc::AsyncObjectWrap {
 public:
  RTCRtpSender(
      std::shared_ptr<node_webrtc::PeerConnectionFactory>&& factory,
      rtc::scoped_refptr<webrtc::RtpSenderInterface>&& sender);

  ~RTCRtpSender() override;

  static void Init(v8::Handle<v8::Object> exports);
  static Nan::Persistent<v8::Function> constructor;
  static NAN_METHOD(New);

  static NAN_GETTER(GetTrack);
  static NAN_GETTER(GetTransport);
  static NAN_GETTER(GetRtcpTransport);

  static NAN_METHOD(GetCapabilities);

  static NAN_METHOD(GetParameters);
  static NAN_METHOD(SetParameters);
  static NAN_METHOD(GetStats);
  static NAN_METHOD(ReplaceTrack);

  rtc::scoped_refptr<webrtc::RtpSenderInterface> sender() { return _sender; }

  static RTCRtpSender* GetOrCreate(
      std::shared_ptr<PeerConnectionFactory>,
      rtc::scoped_refptr<webrtc::RtpSenderInterface>);
  static void Release(RTCRtpSender*);

 private:
  const std::shared_ptr<node_webrtc::PeerConnectionFactory> _factory;
  const rtc::scoped_refptr<webrtc::RtpSenderInterface> _sender;

  static BidiMap<rtc::scoped_refptr<webrtc::RtpSenderInterface>, RTCRtpSender*> _senders;
};

}  // namespace node_webrtc

#endif  // SRC_RTCRTPSENDER_H_