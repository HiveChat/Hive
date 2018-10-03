#include "HiveProtocol.h"

bool
HiveProtocol::decodeTcp(const QString &data, HiveClientBuffer *clientBuffer) //recursion decode
{
  qDebug()<<"\n\n";
  Log::net(Log::Info, "Bee::read()", "New READ section begins");
  if(data.isEmpty() && clientBuffer->buffer.isEmpty())
    {
      Log::net(Log::Warning, "Bee:read()", "data empty");
      return false;
    }

  Log::net(Log::Info, "Bee::read()", "Stream: " + data);
  Log::net(Log::Info, "Bee::read()", "Current Buffer Size: " + QString::number( clientBuffer->buffer.size()));

  clientBuffer->buffer.append(data);

  //if size header is 0
  if(clientBuffer->readSize == 0)
    {
      //if 16 digit size header is not complete, return
      if(clientBuffer->buffer.size() < 16)
        {
          Log::net(Log::Info, "Bee::read()", "Failed: value \"size\" in header is not complete");
          return false;
        }
      else
        {
          clientBuffer->readSize = clientBuffer->buffer.mid(0, 16).toInt();
          clientBuffer->buffer.remove(0, 16);
          Log::net(Log::Info, "Bee::read()", "Member clientBuffer->readSize is set to " + QString::number(clientBuffer->readSize));
        }
    }

  //if data is not complete, return
  if(clientBuffer->buffer.size() < clientBuffer->readSize)
    {
      Log::net(Log::Info, "Bee::read()", "Failed: buffer not filled.");
      return false;
    }
  else //else read
    {
      QString packet = clientBuffer->buffer.mid(0, clientBuffer->readSize - 1);
      clientBuffer->buffer.remove(0, clientBuffer->readSize - 1);
      clientBuffer->readSize = 0;

      Log::net(Log::Info, "Bee::read()", "Get packet: " + packet);

//      if(!decodeHivePacket(packet))
        {
          Log::net(Log::Warning, "bool Bee::readBuffer()", "Packet decode failed!");
          clientBuffer->buffer.clear();

          //have to reset the connection!

          return false;
        }
    }

  return decodeTcp("", clientBuffer);
}

bool HiveProtocol::decodeUdp(const QString &data, const char *addr)
{
  checkJson(data, QString::fromUtf8(addr));
}

bool
HiveProtocol::writeTcp(const MessageType &msgType, const QString &data)
{

}

std::tuple<MessageType, QJsonObject>
HiveProtocol::checkJson(const QString &data, const QString &addr)
{
//  QJsonObject a;
//  return std::make_tuple(MessageType::TextMessage, a);


//  QByteArray byteArray = data.toLatin1();
//  QJsonParseError jsonError;
//  QJsonDocument readJsonDocument = QJsonDocument::fromJson(byteArray, &jsonError);
//  if(jsonError.error != QJsonParseError::NoError && !readJsonDocument.isObject())
//    {
//      Log::net(Log::Critical, "HiveProtocol::decodeHivePacket()", QString(jsonError.errorString() + " in stream: " + data));
//      return false;
//    }

//  QJsonObject packetJson = readJsonDocument.object();
//  QString receiverKey = packetJson.value("receiver").toString();
//  if(receiverKey != GlobalData::settings_struct.profile_key_str
//     && receiverKey != "{00000000-0000-0000-0000-000000000000}")
//    {
//      Log::net(Log::Error, "HiveProtocol::decodeHivePacket()", "Package delivered to wrong person!\n\t"+packetJson.value("receiver").toString() + "\n" + GlobalData::settings_struct.profile_key_str );
//      return false;
//    }
//  MessageType messageType = (MessageType) packetJson.value("msgType").toInt();
//  switch (messageType) {
//    case MessageType::HeartBeat:
//      {
////        UsrProfileStruct usr_profile;
////        usr_profile.ip = addr;
////        usr_profile.key = packetJson.value("sender").toString();
////        usr_profile.name = packetJson.value("name").toString();
////        usr_profile.avatar = packetJson.value("avatar").toString();
////        processHeartBeat(usr_profile);

//        packetJson.insert("ip", addr);

//        return std::make_tuple(MessageType::Null, packetJson);
//      }
//    case MessageType::TextMessage:
//      {
////        processTextMessage();
//        break;
//      }
//    case MessageType::FileInfo:
//      {
//        Log::net(Log::Normal, "HiveProtocol::decodeHivePacket()", "File info received.");

//        break;
//      }
//    case MessageType::FileContent:
//      {

//        break;
//      }
//    case MessageType::FileReject:
//      {

//        break;
//      }
//    case MessageType::FileAccept:
//      {

//        break;
//      }
//    case MessageType::ErrorDelivery:
//      {

//        break;
//      }
//  }

//  return std::make_tuple(MessageType::Null, QJsonObject());
}

//bool
//HiveProtocol::processHeartBeat(const UsrProfileStruct &usrProfileStruct)
//{
//  if(usrProfileStruct.key.isEmpty())
//    {
//      return false;
//    }

//  if(usrProfileStruct.key == GlobalData::settings_struct.profile_key_str)
//    {
//      if(GlobalData::g_localHostIP != usrProfileStruct.ip)
//        {
//          GlobalData::g_localHostIP = usrProfileStruct.ip;
//        }
//      Log::net(Log::Normal, "HiveProtocol::processHeartBeat", "got heart beat from myself");
////      emit getInstance()->usrEntered(usrProfileStruct);
//    }
//  else
//    {
//      Log::net(Log::Normal, "HiveProtocol::processHeartBeat", "got heart beat from others");
////      emit getInstance()->usrEntered(usrProfileStruct);
//    }
//}

//bool
//HiveProtocol::processUsrLeave(QString *usrKey)
//{
//  if(*usrKey == GlobalData::settings_struct.profile_key_str)
//    {
////      emit usrLeft(usrKey); << FIX HERE!!

//      qDebug()<<"@HiveProtocol::udpProcessUsrLeft(): Myself left.";
//    }

//  qDebug()<<"@HiveProtocol::udpProcessUsrLeft(): Someone left.";
////  emit usrLeft(usrKey); << FIX HERE!!
//}

//bool
//HiveProtocol::processErrorDelivery()
//{

//}

//bool
//HiveProtocol::processTextMessage()
//{
////  if(messageStruct.sender.isEmpty() || messageStruct.reciever.isEmpty())
////    {
////      return;
////    }

////  if(messageStruct.reciever != GlobalData::settings_struct.profile_key_str)
////    {
////      if(messageStruct.sender != GlobalData::settings_struct.profile_key_str)
////        {
////          //no sniffing man!
////          return;
////        }
////      else
////        {
////          qDebug()<<"@NetworkManager::udpProcessMessage(): Got msg I sent: "<<messageStruct.message;
////          emit messageRecieved(messageStruct, true);
////        }
////    }
////  else
////    {
////      if(messageStruct.sender == GlobalData::settings_struct.profile_key_str)
////        {
////          qDebug()<<"@NetworkManager::udpProcessMessage(): me 2 me...";
////          emit messageRecieved(messageStruct, true);
////        }
////      else
////        {
////          qDebug()<<"@NetworkManager::udpProcessMessage(): Other people sent: "<<messageStruct.message;
////          emit messageRecieved(messageStruct, false);
////        }
////    }
//}

//bool
//HiveProtocol::processFileInfo()
//{

//}

//bool
//HiveProtocol::processFileContent()
//{

//}

//bool
//HiveProtocol::processFileAccept()
//{

//}

//bool
//HiveProtocol::processFileReject()
//{

//}

QByteArray HiveProtocol::encodeHeartBeat()
{
  QJsonObject jsonObj;
  jsonObj.insert("sender", Global::settings.profile_key_str);
  jsonObj.insert("receiver", "{00000000-0000-0000-0000-000000000000}");
  jsonObj.insert("name", Global::settings.profile_name_str);
  jsonObj.insert("avatar", Global::settings.profile_avatar_str);
  jsonObj.insert("msgType", MessageType::HeartBeat);
  jsonObj.insert("trash", "aiCheila7Ohm8thohquoPhoh9aequ8raa1");
  QJsonDocument jsonDoc(jsonObj);

  return jsonDoc.toJson() + "\0";
}

QByteArray HiveProtocol::encodeTextMessage(const QJsonObject &msg)
{
  QJsonObject jsonObj = msg;
  jsonObj.insert("index", QJsonValue(Global::getRandomString(8)));
  jsonObj.insert("msgType", MessageType::TextMessage);
  QJsonDocument jsonDoc(jsonObj);

  return jsonDoc.toJson() + '\0';
}
