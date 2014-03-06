package.path = package.path..";../../Public/Script/packet/?.lua"

require "packet_const"
require "packet_player"
require "packet_test"


null_str = ""
--包总表
packet = 
{
	[PT.CSTEST] = cstestpacket,
	[PT.SCTEST] = sctestpacket,
	[PT.CSPLAYER] = csplayerpacket,
	id = -1,
}


function x000003_SendPacket(socket, packetid)
	packetid = packetid or packet.id;
	if not packet[packetid] or not packet[packetid].data then		
		return 0;
	end
	local sendBuff = net.GetSocketSendBuff(socket);
	if not sendBuff then
		return 0;
	end
	local tPacket = packet[packetid];
	local tData = packet[packetid].data;
	local sendBuff = net.GetSocketSendBuff(socket);
	net.PreFillBuff(sendBuff, packetid);
	for k, v in pairs(tData) do
		local strType = v[1];		
		net.FillBuff(sendBuff, strType, tPacket.var[k]);				
	end	
	return 0;
end

function x000003_ClearPacket(tPacket)
	local tData = tPacket.data;
	for k, v in pairs(tData) do
		tPacket.var[k] = nil;
	end
end
function x000003_ProcessPacket(socket, packetid)		
	if not packet[packetid] or not packet[packetid].data then
		net.DelConn(socket);	
		return 0;
	end
	local recvBuff = net.GetSocketRecvBuff(socket);
	if not recvBuff then				
		return 0;
	end
	local tPacket = packet[packetid];
	local tData = packet[packetid].data;
	x000003_ClearPacket(tPacket);
	local mapret, mapval
	for k, v in pairs(tData) do
		local strType = v[1];				
		mapret, mapval = net.MapBuff(recvBuff, strType);	
		if mapret==nil or mapret==0 then
			net.RecoverBuff(recvBuff);				
			return 0;
		end		
		tPacket.var[k] = mapval;
	end	
	net.EndParseBuff(recvBuff);
	tPacket:handle(socket);	
	return 1;
end
function x000003_InitPacketData(packetid)
	if not packet[packetid] or not packet[packetid].data then		
		return 0;
	end
	packet.id = packetid;
	local tData = packet[packetid].data;
	for k, v in pairs(tData) do
		packet[packetid].var[k] = v[2];
	end
	return 1;
end

function x000003_SetPacketData(k, val)
	local packetid = packet.id;
	if not packet[packetid] or not packet[packetid].data then		
		return 0;
	end
	local tData = packet[packetid].data;
	if not tData[k] then
		return 0;
	end
	packet[packetid].var[k] = val;
end
