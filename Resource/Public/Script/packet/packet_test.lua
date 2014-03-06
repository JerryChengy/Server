
--从客户端到服务器的测试包
cstestpacket = 
{
	data = 
	{
		{"INT", 0},
		{"STRING", null_str},
		--{"HumanData"}
	},
	var = {},	
}
--从服务器到客户端的测试包
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


function sctestpacket:handle(socket)
	player.HandleSCTestPacket(self.var[1], self.var[2], self.var[3]);
end

function cstestpacket:handle(socket)	
	player.SendSCTestPacket(PT.SCTEST, socket);
end


