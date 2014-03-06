

--从客户端到服务器的角色包
csplayerpacket = 
{
	data = 
	{
		{"INT", 0},
		{"INT", 0},
		{"HumanData", nil}
	},
	var = {},	
}

function csplayerpacket:handle(socket)
	--print("csplayerpacket: var1: "..self.var[1].."var2: "..self.var[2])
	player.HandleCSPlayerPacket(self.var[1], self.var[2], self.var[3]);
end

