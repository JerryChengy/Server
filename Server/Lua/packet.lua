
null_str = ""
cstestpacket = 
{
	data = 
	{
		{"INT"},
		{"STRING"},
		--{"HumanData"}
	},
	var = {},	
}
sctestpacket = 
{
	data = 
	{
		{"INT", 0},
		{"STRING", null_str},
		{"HumanData", nil}
	},
	var = {},	
}
packet = 
{
	[0] = cstestpacket,
	[1] = sctestpacket,
	obj = nil,
	id = -1,
}
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

function x000003_ProcessPacket(socket, packetid)	
	print(111)
	if not packet[packetid] or not packet[packetid].data then
		net.DelConn(socket);	
print(222)		
		return 0;
	end
	local recvBuff = net.GetSocketRecvBuff(socket);
	if not recvBuff then
		print(333)		
		return 0;
	end
	local tPacket = packet[packetid];
	local tData = packet[packetid].data;
	for k, v in pairs(tData) do
		local strType = v[1];		
		tPacket.var[k] = net.MapBuff(recvBuff, strType);		
		if tPacket.var[k]==nil then			
			net.RecoverBuff(recvBuff);
			print(444)		
			return 0;
		end
	end	
	net.EndParseBuff(recvBuff);
	tPacket:handle(socket);	
	return 1;
end



function cstestpacket:handle(socket)
	print(self.var[1],self.var[2])
	-- sctestpacket.var[1] = 555;
	-- sctestpacket.var[2] = "chengyao"
	-- x000003_SendPacket(socket, 1)
	net.SendTestPacket(1, socket);
end
