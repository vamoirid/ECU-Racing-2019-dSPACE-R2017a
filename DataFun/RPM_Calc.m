RPMmax = 1000;

RPM_max = RPMmax;
RPM_maxHex = dec2hex(RPM_max);
RPM_maxHexFinal = '000';

if RPM_max < 26
    RPM_maxHexFinal(1:1) = '0';
    RPM_maxHexFinal(2:3) = IcontHex;
    RPM_maxLhex = RPM_maxHexFinal(2:3);
    RPM_maxHhex = RPM_maxHexFinal(1:1);
    RPM_maxL = hex2dec(RPM_maxLhex);
    RPM_maxH = hex2dec(RPM_maxHhex);
else
    RPM_maxHexFinal = RPM_maxHex;
    RPM_maxLhex = RPM_maxHexFinal(2:3);
    RPM_maxHhex = RPM_maxHexFinal(1:1);
    RPM_maxL = hex2dec(RPM_maxLhex);
    RPM_maxH = hex2dec(RPM_maxHhex);
end