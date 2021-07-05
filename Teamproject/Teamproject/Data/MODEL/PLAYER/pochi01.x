xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 261;
 -4.24065;-1.70036;-1.94166;,
 -1.63726;-3.63854;-2.15640;,
 -1.64036;-4.42543;0.46140;,
 -4.59564;-2.19891;0.70567;,
 1.72255;-3.69193;-2.38724;,
 2.05866;-4.48421;0.20726;,
 4.39082;-1.83752;-2.53469;,
 5.08851;-2.35279;0.04031;,
 5.11717;0.39776;-2.54210;,
 5.96948;0.21495;0.02861;,
 5.87694;2.48015;-2.55469;,
 4.49581;4.29902;-2.42582;,
 5.45200;5.15381;-0.17769;,
 6.36310;2.42574;0.04349;,
 1.89243;6.23720;-2.21108;,
 2.22850;6.92545;0.41144;,
 -1.46738;6.29059;-1.98024;,
 -1.41978;6.98342;0.66209;,
 -4.13566;4.43617;-1.83279;,
 -4.74796;5.31589;0.52310;,
 -5.57825;2.66218;-1.76766;,
 -5.70606;2.61752;0.87271;,
 -7.10555;0.31051;-0.44513;,
 -6.86786;-0.51554;-0.47701;,
 -7.53573;-1.38822;0.92212;,
 -7.82582;-0.43875;0.95991;,
 -1.62622;-0.82939;-11.50173;,
 -2.97332;0.07942;-11.39240;,
 -0.51205;1.47617;-11.53435;,
 0.52265;-0.86354;-11.64936;,
 1.90011;0.00198;-11.72723;,
 2.13829;1.43405;-11.71645;,
 2.07448;1.05037;-11.71933;,
 1.94923;2.87292;-11.67631;,
 0.60213;3.78172;-11.56697;,
 -1.54674;3.81587;-11.41932;,
 -2.92421;2.95036;-11.34147;,
 -3.16238;1.51828;-11.35226;,
 -3.11173;1.13278;-11.36301;,
 -3.25941;-1.40290;1.34656;,
 -1.79651;-3.09276;1.21453;,
 0.35557;1.23630;1.14919;,
 2.35839;-3.15878;0.92906;,
 3.87830;-1.51632;0.85616;,
 4.32911;0.45067;0.86252;,
 5.29277;1.96647;0.82526;,
 3.45114;2.65286;0.96422;,
 1.76510;5.04895;1.12488;,
 -0.92276;5.09165;1.30955;,
 -2.68985;2.75044;1.38614;,
 -4.55397;2.12294;1.50179;,
 -3.64268;0.57734;1.41022;,
 8.05474;-1.63596;-0.14904;,
 7.22977;-0.73956;-1.44560;,
 7.49558;0.07851;-1.44831;,
 8.37715;-0.69622;-0.15332;,
 -5.38829;0.39543;0.80895;,
 -4.89013;0.55678;-1.85454;,
 -4.24065;-1.70036;-1.94166;,
 -4.59564;-2.19891;0.70567;,
 -3.86713;-1.17581;-4.72706;,
 -1.63401;-2.81060;-4.91073;,
 1.36890;-2.85832;-5.11705;,
 3.65674;-1.29536;-5.24399;,
 4.22040;0.59010;-5.24689;,
 7.68241;-0.80754;-2.74037;,
 7.41659;-1.62560;-2.73766;,
 5.70373;-0.52836;-4.60599;,
 5.91002;0.16167;-4.60705;,
 4.92063;2.54447;-5.25783;,
 3.74526;3.87871;-5.15219;,
 1.51214;5.51350;-4.96852;,
 -1.49077;5.56122;-4.76220;,
 -3.77861;3.99826;-4.63526;,
 -4.99898;2.70210;-4.57630;,
 -5.96494;0.35036;-3.79118;,
 -5.78237;-0.34585;-3.81683;,
 -7.25751;-1.39243;-1.72947;,
 -7.49521;-0.56637;-1.69758;,
 -4.36599;0.72654;-4.65696;,
 -3.86713;-1.17581;-4.72706;,
 -2.97332;0.07942;-11.39240;,
 -1.62622;-0.82939;-11.50173;,
 0.52265;-0.86354;-11.64936;,
 1.90011;0.00198;-11.72723;,
 2.07448;1.05037;-11.71933;,
 2.13829;1.43405;-11.71645;,
 1.94923;2.87292;-11.67631;,
 0.60213;3.78172;-11.56697;,
 -1.54674;3.81587;-11.41932;,
 -2.92421;2.95036;-11.34147;,
 -3.16238;1.51828;-11.35226;,
 -3.11173;1.13278;-11.36301;,
 -2.97332;0.07942;-11.39240;,
 -4.59564;-2.19891;0.70567;,
 -1.64036;-4.42543;0.46140;,
 2.05866;-4.48421;0.20726;,
 5.08851;-2.35279;0.04031;,
 5.96948;0.21495;0.02861;,
 6.36310;2.42574;0.04349;,
 7.06808;4.13596;2.37378;,
 6.72802;5.69874;3.82239;,
 5.77310;4.95290;4.89444;,
 6.68064;3.54590;2.95156;,
 4.91558;6.15264;2.33504;,
 3.65495;6.00695;2.75393;,
 2.22850;6.92545;0.41144;,
 -1.41978;6.98342;0.66209;,
 -3.84169;6.29180;2.93671;,
 -5.44718;5.89221;4.65889;,
 -4.37871;5.11421;5.59193;,
 -2.54087;6.10540;3.17962;,
 -6.03137;4.34412;3.27378;,
 -5.58742;3.74084;3.79445;,
 -5.70606;2.61752;0.87271;,
 -5.38829;0.39543;0.80895;,
 6.56550;5.48203;2.46767;,
 -4.74796;5.31589;0.52310;,
 -5.47835;5.67341;3.29515;,
 5.45200;5.15381;-0.17769;,
 4.22221;3.68685;-3.89723;,
 5.05790;3.67357;-3.95464;,
 5.39655;3.12618;-3.37333;,
 3.94910;3.14919;-3.27388;,
 5.48816;4.39224;-3.97048;,
 6.14177;4.37094;-3.40077;,
 5.08272;5.12417;-3.92891;,
 5.43954;5.63871;-3.32876;,
 4.24703;5.13745;-3.87149;,
 3.99208;5.66170;-3.22931;,
 3.81678;4.41879;-3.85565;,
 3.24687;4.41694;-3.20187;,
 4.22221;3.68685;-3.89723;,
 3.94910;3.14919;-3.27388;,
 5.56235;2.91425;-2.54881;,
 3.89098;2.94081;-2.43398;,
 6.42286;4.35158;-2.58049;,
 5.61199;5.81546;-2.49734;,
 3.94061;5.84203;-2.38251;,
 3.08011;4.40470;-2.35083;,
 3.89098;2.94081;-2.43398;,
 5.51087;3.09458;-1.70201;,
 4.06342;3.11758;-1.60256;,
 6.25610;4.33934;-1.72945;,
 5.55386;5.60710;-1.65743;,
 4.10641;5.63010;-1.55799;,
 3.36119;4.38534;-1.53055;,
 4.06342;3.11758;-1.60256;,
 5.25592;3.61882;-1.05983;,
 4.42024;3.63211;-1.00241;,
 5.68618;4.33748;-1.07567;,
 5.28074;5.06943;-1.03410;,
 4.44505;5.08271;-0.97668;,
 4.01480;4.36404;-0.96084;,
 4.42024;3.63211;-1.00241;,
 4.63715;4.40975;-4.13698;,
 4.63715;4.40975;-4.13698;,
 4.63715;4.40975;-4.13698;,
 4.63715;4.40975;-4.13698;,
 4.63715;4.40975;-4.13698;,
 4.63715;4.40975;-4.13698;,
 4.86581;4.34653;-0.79434;,
 4.86581;4.34653;-0.79434;,
 4.86581;4.34653;-0.79434;,
 4.86581;4.34653;-0.79434;,
 4.86581;4.34653;-0.79434;,
 4.86581;4.34653;-0.79434;,
 -4.93893;3.83243;-3.26780;,
 -4.10324;3.81914;-3.32522;,
 -3.76460;3.27176;-2.74391;,
 -5.21205;3.29476;-2.64446;,
 -3.67299;4.53781;-3.34106;,
 -3.01938;4.51651;-2.77135;,
 -4.07842;5.26975;-3.29948;,
 -3.72161;5.78427;-2.69933;,
 -4.91411;5.28303;-3.24207;,
 -5.16906;5.80728;-2.59989;,
 -5.34436;4.56437;-3.22623;,
 -5.91428;4.56252;-2.57245;,
 -4.93893;3.83243;-3.26780;,
 -5.21205;3.29476;-2.64446;,
 -3.59879;3.05983;-1.91939;,
 -5.27017;3.08638;-1.80456;,
 -2.73829;4.49716;-1.95107;,
 -3.54916;5.96103;-1.86792;,
 -5.22053;5.98759;-1.75309;,
 -6.08104;4.55027;-1.72140;,
 -5.27017;3.08638;-1.80456;,
 -3.65027;3.24015;-1.07259;,
 -5.09772;3.26315;-0.97314;,
 -2.90505;4.48491;-1.10002;,
 -3.60728;5.75267;-1.02801;,
 -5.05474;5.77567;-0.92857;,
 -5.79995;4.53091;-0.90113;,
 -5.09772;3.26315;-0.97314;,
 -3.90522;3.76439;-0.43041;,
 -4.74091;3.77768;-0.37299;,
 -3.47497;4.48306;-0.44625;,
 -3.88041;5.21500;-0.40467;,
 -4.71609;5.22828;-0.34726;,
 -5.14634;4.50962;-0.33142;,
 -4.74091;3.77768;-0.37299;,
 -4.52399;4.55532;-3.50756;,
 -4.52399;4.55532;-3.50756;,
 -4.52399;4.55532;-3.50756;,
 -4.52399;4.55532;-3.50756;,
 -4.52399;4.55532;-3.50756;,
 -4.52399;4.55532;-3.50756;,
 -4.29534;4.49211;-0.16492;,
 -4.29534;4.49211;-0.16492;,
 -4.29534;4.49211;-0.16492;,
 -4.29534;4.49211;-0.16492;,
 -4.29534;4.49211;-0.16492;,
 -4.29534;4.49211;-0.16492;,
 -1.10751;2.12104;-12.44047;,
 0.01757;2.10317;-12.51778;,
 0.46219;1.46857;-11.92316;,
 -1.48651;1.49953;-11.78928;,
 0.59451;2.93579;-12.54149;,
 1.46148;2.91072;-11.96425;,
 0.04636;3.78629;-12.48791;,
 0.51207;4.38383;-11.87144;,
 -1.07872;3.80417;-12.41061;,
 -1.43663;4.41479;-11.73756;,
 -1.65566;2.97155;-12.38689;,
 -2.43592;2.97265;-11.69647;,
 -1.10751;2.12104;-12.44047;,
 -1.48651;1.49953;-11.78928;,
 0.66829;1.22431;-11.07169;,
 -1.58187;1.26006;-10.91710;,
 1.82217;2.88955;-11.11913;,
 0.72589;4.59056;-11.01198;,
 -1.52428;4.62631;-10.85738;,
 -2.67815;2.96106;-10.80994;,
 -1.58187;1.26006;-10.91710;,
 0.58065;1.43582;-10.19150;,
 -1.36806;1.46678;-10.05761;,
 1.57994;2.87797;-10.23259;,
 0.63052;4.35108;-10.13979;,
 -1.31817;4.38205;-10.00589;,
 -2.31746;2.93990;-9.96482;,
 -1.36806;1.46678;-10.05761;,
 0.22274;2.04645;-9.51845;,
 -0.90234;2.06432;-9.44115;,
 0.79968;2.87907;-9.54216;,
 0.25153;3.72957;-9.48858;,
 -0.87355;3.74745;-9.41128;,
 -1.45049;2.91482;-9.38756;,
 -0.90234;2.06432;-9.44115;,
 -0.54645;2.95806;-12.69620;,
 -0.54645;2.95806;-12.69620;,
 -0.54645;2.95806;-12.69620;,
 -0.54645;2.95806;-12.69620;,
 -0.54645;2.95806;-12.69620;,
 -0.54645;2.95806;-12.69620;,
 -0.30954;2.89256;-9.23287;,
 -0.30954;2.89256;-9.23287;,
 -0.30954;2.89256;-9.23287;,
 -0.30954;2.89256;-9.23287;,
 -0.30954;2.89256;-9.23287;,
 -0.30954;2.89256;-9.23287;;
 
 210;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;10,11,12,13;,
 4;11,14,15,12;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;22,23,24,25;,
 3;26,27,28;,
 3;29,26,28;,
 3;30,29,28;,
 4;31,32,30,28;,
 3;33,31,28;,
 3;34,33,28;,
 3;35,34,28;,
 3;36,35,28;,
 3;37,36,28;,
 4;27,38,37,28;,
 3;39,40,41;,
 3;40,42,41;,
 3;42,43,41;,
 3;41,44,45;,
 3;45,46,41;,
 3;46,47,41;,
 3;47,48,41;,
 3;48,49,41;,
 3;49,50,41;,
 3;50,51,41;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 3;41,51,39;,
 3;43,44,41;,
 4;60,61,1,0;,
 4;61,62,4,1;,
 4;62,63,6,4;,
 4;63,64,8,6;,
 4;65,66,67,68;,
 4;69,70,11,10;,
 4;70,71,14,11;,
 4;71,72,16,14;,
 4;72,73,18,16;,
 4;73,74,20,18;,
 4;75,76,77,78;,
 4;58,57,79,80;,
 4;81,82,61,60;,
 4;82,83,62,61;,
 4;83,84,63,62;,
 4;84,85,64,63;,
 4;69,64,85,86;,
 4;86,87,70,69;,
 4;87,88,71,70;,
 4;88,89,72,71;,
 4;89,90,73,72;,
 4;90,91,74,73;,
 4;91,92,79,74;,
 4;80,79,92,93;,
 4;20,57,23,22;,
 4;57,56,24,23;,
 4;56,21,25,24;,
 4;21,20,22,25;,
 4;9,8,53,52;,
 4;8,10,54,53;,
 4;10,13,55,54;,
 4;13,9,52,55;,
 4;10,8,66,65;,
 4;8,64,67,66;,
 4;64,69,68,67;,
 4;69,10,65,68;,
 4;74,79,76,75;,
 4;79,57,77,76;,
 4;57,20,78,77;,
 4;20,74,75,78;,
 4;94,95,40,39;,
 4;95,96,42,40;,
 4;96,97,43,42;,
 4;98,99,45,44;,
 4;100,101,102,103;,
 4;101,104,105,102;,
 4;106,107,48,47;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;114,115,51,50;,
 4;115,94,39,51;,
 4;97,98,44,43;,
 3;100,116,101;,
 4;46,45,103,102;,
 4;45,99,100,103;,
 3;116,104,101;,
 4;106,47,105,104;,
 4;47,46,102,105;,
 4;107,117,118,108;,
 4;49,48,111,110;,
 4;48,107,108,111;,
 4;117,114,112,118;,
 4;114,50,113,112;,
 4;50,49,110,113;,
 3;118,112,109;,
 3;108,118,109;,
 4;99,119,116,100;,
 4;119,106,104,116;,
 4;120,121,122,123;,
 4;121,124,125,122;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;123,122,134,135;,
 4;122,125,136,134;,
 4;125,127,137,136;,
 4;127,129,138,137;,
 4;129,131,139,138;,
 4;131,133,140,139;,
 4;135,134,141,142;,
 4;134,136,143,141;,
 4;136,137,144,143;,
 4;137,138,145,144;,
 4;138,139,146,145;,
 4;139,140,147,146;,
 4;142,141,148,149;,
 4;141,143,150,148;,
 4;143,144,151,150;,
 4;144,145,152,151;,
 4;145,146,153,152;,
 4;146,147,154,153;,
 3;121,120,155;,
 3;124,121,156;,
 3;126,124,157;,
 3;128,126,158;,
 3;130,128,159;,
 3;132,130,160;,
 3;149,148,161;,
 3;148,150,162;,
 3;150,151,163;,
 3;151,152,164;,
 3;152,153,165;,
 3;153,154,166;,
 4;167,168,169,170;,
 4;168,171,172,169;,
 4;171,173,174,172;,
 4;173,175,176,174;,
 4;175,177,178,176;,
 4;177,179,180,178;,
 4;170,169,181,182;,
 4;169,172,183,181;,
 4;172,174,184,183;,
 4;174,176,185,184;,
 4;176,178,186,185;,
 4;178,180,187,186;,
 4;182,181,188,189;,
 4;181,183,190,188;,
 4;183,184,191,190;,
 4;184,185,192,191;,
 4;185,186,193,192;,
 4;186,187,194,193;,
 4;189,188,195,196;,
 4;188,190,197,195;,
 4;190,191,198,197;,
 4;191,192,199,198;,
 4;192,193,200,199;,
 4;193,194,201,200;,
 3;168,167,202;,
 3;171,168,203;,
 3;173,171,204;,
 3;175,173,205;,
 3;177,175,206;,
 3;179,177,207;,
 3;196,195,208;,
 3;195,197,209;,
 3;197,198,210;,
 3;198,199,211;,
 3;199,200,212;,
 3;200,201,213;,
 4;214,215,216,217;,
 4;215,218,219,216;,
 4;218,220,221,219;,
 4;220,222,223,221;,
 4;222,224,225,223;,
 4;224,226,227,225;,
 4;217,216,228,229;,
 4;216,219,230,228;,
 4;219,221,231,230;,
 4;221,223,232,231;,
 4;223,225,233,232;,
 4;225,227,234,233;,
 4;229,228,235,236;,
 4;228,230,237,235;,
 4;230,231,238,237;,
 4;231,232,239,238;,
 4;232,233,240,239;,
 4;233,234,241,240;,
 4;236,235,242,243;,
 4;235,237,244,242;,
 4;237,238,245,244;,
 4;238,239,246,245;,
 4;239,240,247,246;,
 4;240,241,248,247;,
 3;215,214,249;,
 3;218,215,250;,
 3;220,218,251;,
 3;222,220,252;,
 3;224,222,253;,
 3;226,224,254;,
 3;243,242,255;,
 3;242,244,256;,
 3;244,245,257;,
 3;245,246,258;,
 3;246,247,259;,
 3;247,248,260;;
 
 MeshMaterialList {
  3;
  210;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.240000;0.240000;0.240000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.592000;0.168000;0.424000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  239;
  -0.068234;0.018861;-0.997491;,
  -0.068233;0.018860;-0.997491;,
  -0.068233;0.018859;-0.997491;,
  -0.068235;0.018858;-0.997491;,
  -0.068235;0.018859;-0.997491;,
  -0.068236;0.018862;-0.997491;,
  -0.068236;0.018864;-0.997491;,
  -0.068233;0.018864;-0.997491;,
  -0.068232;0.018863;-0.997491;,
  -0.068233;0.018861;-0.997491;,
  -0.808121;-0.547392;-0.217491;,
  -0.330200;-0.904411;-0.270202;,
  0.261387;-0.913811;-0.310847;,
  0.753075;-0.572200;-0.324754;,
  0.851549;0.423825;-0.308603;,
  0.679195;0.637593;-0.363550;,
  0.296712;0.903816;-0.308348;,
  -0.307354;0.913415;-0.266845;,
  -0.702020;0.659540;-0.268653;,
  -0.871915;0.451212;-0.190191;,
  -0.068234;0.018861;-0.997491;,
  -0.068234;0.018858;-0.997491;,
  0.900530;-0.302017;-0.312780;,
  -0.068233;0.018862;-0.997491;,
  -0.943936;-0.272708;-0.186054;,
  -0.809868;-0.544693;-0.217769;,
  -0.328640;-0.904981;-0.270196;,
  0.259825;-0.914331;-0.310627;,
  0.754852;-0.569557;-0.325274;,
  0.792762;-0.261379;-0.550645;,
  0.818746;0.492140;-0.295727;,
  0.664628;0.676082;-0.318091;,
  0.264112;0.915094;-0.304708;,
  -0.274223;0.923649;-0.267721;,
  -0.680164;0.697451;-0.225695;,
  -0.835515;0.518426;-0.182069;,
  -0.868472;-0.234982;-0.436509;,
  -0.818200;-0.531431;-0.219385;,
  -0.321808;-0.907511;-0.269933;,
  0.253017;-0.916645;-0.309427;,
  0.763300;-0.556561;-0.328043;,
  0.829657;-0.228159;-0.509523;,
  0.821434;0.235243;-0.519526;,
  0.680949;0.665643;-0.305331;,
  0.284403;0.917852;-0.276880;,
  -0.290421;0.926986;-0.237387;,
  -0.694909;0.687506;-0.210801;,
  -0.876901;0.262229;-0.402842;,
  -0.898329;-0.200701;-0.390800;,
  -0.829047;0.076361;-0.553940;,
  -0.686267;-0.178450;-0.705119;,
  -0.816816;-0.221406;-0.532721;,
  -0.922486;0.182786;-0.340013;,
  0.577422;-0.198526;-0.791941;,
  0.728893;-0.245962;-0.638919;,
  0.747517;0.051311;-0.662258;,
  0.872646;0.154263;-0.463349;,
  0.655695;-0.206281;-0.726300;,
  0.794332;0.086725;-0.601261;,
  0.501745;-0.161857;-0.849738;,
  0.660488;0.018932;-0.750598;,
  -0.755983;0.041439;-0.653279;,
  -0.618084;-0.144063;-0.772799;,
  -0.755037;-0.183864;-0.629375;,
  -0.865939;0.113106;-0.487192;,
  -0.125431;-0.143592;0.981656;,
  -0.025258;-0.239893;0.970471;,
  0.068233;-0.018865;0.997491;,
  0.150116;-0.242680;0.958422;,
  0.253871;-0.149619;0.955596;,
  0.286080;-0.089548;0.954012;,
  0.136395;-0.274058;0.951992;,
  -0.182025;-0.322542;0.928888;,
  -0.187657;0.165575;0.968179;,
  0.323415;0.157455;0.933065;,
  0.297032;-0.330155;0.895974;,
  -0.013546;-0.271676;0.962294;,
  -0.155638;-0.082528;0.984361;,
  0.997527;-0.067299;0.020283;,
  0.981639;0.078722;0.173747;,
  0.850704;-0.213093;0.480514;,
  0.820167;-0.458072;0.342776;,
  0.095422;0.984077;0.149959;,
  -0.232203;0.836998;0.495495;,
  -0.042854;0.986274;0.159459;,
  -0.121379;0.980250;0.156134;,
  0.152587;0.891622;0.426294;,
  0.324122;0.828159;0.457271;,
  -0.931958;-0.171950;0.319199;,
  -0.779668;-0.432650;0.452693;,
  -0.706639;0.682574;-0.186421;,
  0.695742;0.660290;-0.282773;,
  -0.312237;-0.405912;-0.858920;,
  0.178866;-0.413717;-0.892662;,
  0.431711;0.008617;-0.901971;,
  0.193452;0.438753;-0.877537;,
  -0.297650;0.446556;-0.843796;,
  -0.550495;0.024224;-0.834487;,
  -0.477327;-0.729976;-0.489177;,
  0.382630;-0.743642;-0.548262;,
  0.825379;-0.004105;-0.564564;,
  0.408169;0.749096;-0.521779;,
  -0.451787;0.762760;-0.462695;,
  -0.894535;0.023225;-0.446394;,
  -0.513575;-0.857837;0.018908;,
  0.483947;-0.873689;-0.049627;,
  0.997523;-0.015851;-0.068536;,
  0.513572;0.857838;-0.018909;,
  -0.483949;0.873688;0.049627;,
  -0.997523;0.015852;0.068536;,
  -0.408173;-0.749095;0.521778;,
  0.451784;-0.762761;0.462695;,
  0.894534;-0.023225;0.446397;,
  0.477324;0.729976;0.489179;,
  -0.382632;0.743640;0.548262;,
  -0.825381;0.004105;0.564562;,
  -0.193455;-0.438753;0.877537;,
  0.297650;-0.446557;0.843796;,
  0.550495;-0.024223;0.834487;,
  0.312235;0.405914;0.858920;,
  -0.178869;0.413717;0.892661;,
  -0.431714;-0.008616;0.901969;,
  -0.068234;0.018865;-0.997491;,
  0.068233;-0.018862;0.997491;,
  -0.312237;-0.405912;-0.858920;,
  0.178867;-0.413717;-0.892662;,
  0.431712;0.008617;-0.901970;,
  0.193452;0.438753;-0.877537;,
  -0.297651;0.446556;-0.843796;,
  -0.550494;0.024224;-0.834488;,
  -0.477327;-0.729976;-0.489177;,
  0.382631;-0.743641;-0.548262;,
  0.825380;-0.004104;-0.564563;,
  0.408171;0.749096;-0.521777;,
  -0.451787;0.762761;-0.462693;,
  -0.894536;0.023225;-0.446392;,
  -0.513574;-0.857837;0.018909;,
  0.483949;-0.873688;-0.049628;,
  0.997523;-0.015849;-0.068536;,
  0.513572;0.857838;-0.018908;,
  -0.483949;0.873688;0.049628;,
  -0.997523;0.015852;0.068537;,
  -0.408172;-0.749095;0.521778;,
  0.451785;-0.762761;0.462694;,
  0.894535;-0.023223;0.446395;,
  0.477324;0.729979;0.489177;,
  -0.382632;0.743641;0.548261;,
  -0.825381;0.004106;0.564562;,
  -0.193455;-0.438752;0.877537;,
  0.297648;-0.446559;0.843795;,
  0.550493;-0.024223;0.834488;,
  0.312234;0.405917;0.858919;,
  -0.178869;0.413717;0.892661;,
  -0.431713;-0.008616;0.901970;,
  -0.068234;0.018865;-0.997491;,
  0.068231;-0.018863;0.997491;,
  -0.270697;-0.377709;-0.885471;,
  0.135000;-0.384155;-0.913345;,
  0.346144;0.010722;-0.938120;,
  0.148613;0.411460;-0.899230;,
  -0.257084;0.417907;-0.871356;,
  -0.470650;0.023700;-0.882001;,
  -0.435760;-0.719702;-0.540502;,
  0.334784;-0.731947;-0.593441;,
  0.760307;-0.001485;-0.649562;,
  0.359979;0.740653;-0.567317;,
  -0.410565;0.752897;-0.514376;,
  -0.841645;0.023972;-0.539498;,
  -0.483047;-0.875439;0.016484;,
  0.452836;-0.890311;-0.047816;,
  0.819229;-0.569562;-0.066812;,
  0.483046;0.875440;-0.016489;,
  -0.452836;0.890311;0.047811;,
  -0.819229;0.569561;0.066808;,
  -0.359982;-0.740654;0.567314;,
  0.410565;-0.752898;0.514374;,
  0.765696;-0.225271;0.602463;,
  0.435761;0.719705;0.540498;,
  -0.334785;0.731949;0.593439;,
  -0.675977;0.200467;0.709132;,
  -0.148611;-0.411461;0.899230;,
  0.257081;-0.417907;0.871357;,
  0.470647;-0.023702;0.882003;,
  0.270695;0.377708;0.885472;,
  -0.134999;0.384155;0.913346;,
  -0.346142;-0.010723;0.938121;,
  -0.068234;0.018865;-0.997491;,
  0.068234;-0.018868;0.997491;,
  -0.824768;-0.520618;-0.220711;,
  -0.316544;-0.909438;-0.269670;,
  0.247780;-0.918406;-0.308442;,
  0.769964;-0.545959;-0.330278;,
  0.920563;-0.225633;-0.318833;,
  0.926422;0.087852;-0.366092;,
  0.710625;0.620292;-0.332040;,
  0.279229;0.919755;-0.275830;,
  -0.285094;0.928722;-0.237058;,
  -0.729376;0.643174;-0.233104;,
  -0.964532;0.117899;-0.236173;,
  -0.962182;-0.195715;-0.189477;,
  -0.522359;-0.126820;-0.843242;,
  0.601060;-0.799203;-0.000824;,
  0.565891;-0.821581;-0.069080;,
  -0.230226;-0.103265;0.967643;,
  -0.174374;-0.094844;0.980101;,
  0.068234;-0.018864;0.997491;,
  -0.595716;-0.803123;0.010729;,
  -0.620497;-0.779793;0.083104;,
  0.397883;-0.141440;-0.906468;,
  0.303659;-0.102440;0.947258;,
  0.356988;-0.112596;0.927298;,
  0.068233;-0.018864;0.997491;,
  0.068233;-0.018864;0.997491;,
  -0.641308;-0.751476;0.154947;,
  0.632385;-0.771713;0.067438;,
  0.068233;-0.018864;0.997491;,
  -0.314401;-0.261893;0.912449;,
  -0.118700;-0.450044;0.885082;,
  0.224311;-0.455494;0.861516;,
  0.427767;-0.273686;0.861459;,
  0.172524;0.975580;0.135942;,
  -0.064595;0.895073;0.441217;,
  -0.173250;0.586246;0.791391;,
  0.298281;0.578755;0.758994;,
  -0.945677;0.109350;0.306166;,
  -0.783322;-0.187126;0.592782;,
  -0.162611;-0.773936;0.612029;,
  -0.414607;-0.587123;0.695261;,
  0.724084;-0.666442;0.177644;,
  -0.622933;-0.338468;0.705261;,
  0.702496;-0.359530;0.614196;,
  0.487001;-0.601450;0.633315;,
  -0.895544;0.326264;-0.302578;,
  -0.713703;-0.643597;0.276426;,
  0.220210;-0.780020;0.585727;,
  0.838268;0.543224;-0.047070;,
  -0.838269;-0.543221;0.047067;,
  0.824215;0.516589;0.231959;,
  -0.786298;-0.527070;0.322386;;
  210;
  4;25,26,11,10;,
  4;26,27,12,11;,
  4;27,28,13,12;,
  4;28,29,22,13;,
  4;30,31,15,14;,
  4;31,32,16,15;,
  4;32,33,17,16;,
  4;33,34,18,17;,
  4;34,35,19,18;,
  4;49,50,51,52;,
  3;1,0,20;,
  3;2,1,20;,
  3;3,2,20;,
  4;4,21,3,20;,
  3;5,4,20;,
  3;6,5,20;,
  3;7,6,20;,
  3;8,7,20;,
  3;9,8,20;,
  4;0,23,9,20;,
  3;65,66,67;,
  3;66,68,67;,
  3;68,69,67;,
  3;67,70,71;,
  3;71,72,67;,
  3;72,73,67;,
  3;73,74,67;,
  3;74,75,67;,
  3;75,76,67;,
  3;76,77,67;,
  4;54,53,55,56;,
  4;24,36,25,10;,
  3;67,77,65;,
  3;69,70,67;,
  4;37,38,26,25;,
  4;38,39,27,26;,
  4;39,40,28,27;,
  4;40,41,29,28;,
  4;58,57,59,60;,
  4;42,43,31,30;,
  4;43,44,32,31;,
  4;44,45,33,32;,
  4;45,46,34,33;,
  4;46,47,35,34;,
  4;61,62,63,64;,
  4;25,36,48,37;,
  4;188,189,38,37;,
  4;189,190,39,38;,
  4;190,191,40,39;,
  4;191,192,41,40;,
  4;42,41,192,193;,
  4;193,194,43,42;,
  4;194,195,44,43;,
  4;195,196,45,44;,
  4;196,197,46,45;,
  4;197,198,47,46;,
  4;198,199,48,47;,
  4;37,48,199,188;,
  4;200,36,50,49;,
  4;201,202,202,202;,
  4;203,204,205,205;,
  4;19,35,49,52;,
  4;206,207,206,206;,
  4;29,208,55,53;,
  4;30,14,56,55;,
  4;209,210,211,211;,
  4;212,212,212,212;,
  4;207,213,213,213;,
  4;41,42,60,59;,
  4;42,30,58,60;,
  4;47,48,62,61;,
  4;214,201,214,214;,
  4;215,215,215,215;,
  4;35,47,61,64;,
  4;216,217,66,65;,
  4;217,218,68,66;,
  4;218,219,69,68;,
  4;210,209,71,70;,
  4;78,79,80,81;,
  4;220,82,83,221;,
  4;222,223,74,73;,
  4;84,85,86,87;,
  4;224,88,89,225;,
  4;204,203,77,76;,
  4;203,216,65,77;,
  4;219,210,70,69;,
  3;78,91,79;,
  4;72,71,226,227;,
  4;228,228,78,81;,
  3;91,82,220;,
  4;222,73,83,82;,
  4;73,72,227,229;,
  4;17,18,90,84;,
  4;75,74,230,231;,
  4;74,223,84,87;,
  4;18,19,232,90;,
  4;233,233,89,88;,
  4;76,75,231,234;,
  3;90,88,224;,
  3;84,90,85;,
  4;14,15,91,78;,
  4;15,16,82,91;,
  4;92,93,99,98;,
  4;93,94,100,99;,
  4;94,95,101,100;,
  4;95,96,102,101;,
  4;96,97,103,102;,
  4;97,92,98,103;,
  4;98,99,105,104;,
  4;99,100,106,105;,
  4;100,101,107,106;,
  4;101,102,108,107;,
  4;102,103,109,108;,
  4;103,98,104,109;,
  4;104,105,111,110;,
  4;105,106,112,111;,
  4;106,107,113,112;,
  4;107,108,114,113;,
  4;108,109,115,114;,
  4;109,104,110,115;,
  4;110,111,117,116;,
  4;111,112,118,117;,
  4;112,113,119,118;,
  4;113,114,120,119;,
  4;114,115,121,120;,
  4;115,110,116,121;,
  3;93,92,122;,
  3;94,93,122;,
  3;95,94,122;,
  3;96,95,122;,
  3;97,96,122;,
  3;92,97,122;,
  3;116,117,123;,
  3;117,118,123;,
  3;118,119,123;,
  3;119,120,123;,
  3;120,121,123;,
  3;121,116,123;,
  4;124,125,131,130;,
  4;125,126,132,131;,
  4;126,127,133,132;,
  4;127,128,134,133;,
  4;128,129,135,134;,
  4;129,124,130,135;,
  4;130,131,137,136;,
  4;131,132,138,137;,
  4;132,133,139,138;,
  4;133,134,140,139;,
  4;134,135,141,140;,
  4;135,130,136,141;,
  4;136,137,143,142;,
  4;137,138,144,143;,
  4;138,139,145,144;,
  4;139,140,146,145;,
  4;140,141,147,146;,
  4;141,136,142,147;,
  4;142,143,149,148;,
  4;143,144,150,149;,
  4;144,145,151,150;,
  4;145,146,152,151;,
  4;146,147,153,152;,
  4;147,142,148,153;,
  3;125,124,154;,
  3;126,125,154;,
  3;127,126,154;,
  3;128,127,154;,
  3;129,128,154;,
  3;124,129,154;,
  3;148,149,155;,
  3;149,150,155;,
  3;150,151,155;,
  3;151,152,155;,
  3;152,153,155;,
  3;153,148,155;,
  4;156,157,163,162;,
  4;157,158,164,163;,
  4;158,159,165,164;,
  4;159,160,166,165;,
  4;160,161,167,166;,
  4;161,156,162,167;,
  4;162,163,169,168;,
  4;163,164,170,169;,
  4;164,165,171,235;,
  4;165,166,172,171;,
  4;166,167,173,172;,
  4;167,162,168,236;,
  4;168,169,175,174;,
  4;169,170,176,175;,
  4;235,171,177,237;,
  4;171,172,178,177;,
  4;172,173,179,178;,
  4;236,168,174,238;,
  4;174,175,181,180;,
  4;175,176,182,181;,
  4;176,177,183,182;,
  4;177,178,184,183;,
  4;178,179,185,184;,
  4;179,174,180,185;,
  3;157,156,186;,
  3;158,157,186;,
  3;159,158,186;,
  3;160,159,186;,
  3;161,160,186;,
  3;156,161,186;,
  3;180,181,187;,
  3;181,182,187;,
  3;182,183,187;,
  3;183,184,187;,
  3;184,185,187;,
  3;185,180,187;;
 }
 MeshTextureCoords {
  261;
  0.375000;0.606176;,
  0.400000;0.606176;,
  0.400000;0.688440;,
  0.375000;0.688440;,
  0.425000;0.606176;,
  0.425000;0.688440;,
  0.450000;0.606176;,
  0.450000;0.688440;,
  0.468302;0.606176;,
  0.468302;0.688440;,
  0.475000;0.606176;,
  0.500000;0.606176;,
  0.500000;0.688440;,
  0.475000;0.688440;,
  0.525000;0.606176;,
  0.525000;0.688440;,
  0.550000;0.606176;,
  0.550000;0.688440;,
  0.575000;0.606176;,
  0.575000;0.688440;,
  0.600000;0.606176;,
  0.600000;0.688440;,
  0.600000;0.606176;,
  0.606698;0.606176;,
  0.606698;0.688440;,
  0.600000;0.688440;,
  0.548284;0.007647;,
  0.626409;0.064409;,
  0.500000;0.150000;,
  0.451716;0.007647;,
  0.373591;0.064409;,
  0.343750;0.156250;,
  0.351745;0.131644;,
  0.373591;0.248091;,
  0.451716;0.304853;,
  0.548284;0.304853;,
  0.626409;0.248091;,
  0.656250;0.156250;,
  0.648255;0.131644;,
  0.626409;0.935591;,
  0.548284;0.992353;,
  0.500000;0.837500;,
  0.451716;0.992353;,
  0.373591;0.935591;,
  0.351745;0.868356;,
  0.343750;0.843750;,
  0.373591;0.751909;,
  0.451716;0.695147;,
  0.548284;0.695147;,
  0.626409;0.751909;,
  0.656250;0.843750;,
  0.648255;0.868356;,
  0.468302;0.688440;,
  0.468302;0.606176;,
  0.475000;0.606176;,
  0.475000;0.688440;,
  0.606698;0.688440;,
  0.606698;0.606176;,
  0.625000;0.606176;,
  0.625000;0.688440;,
  0.375000;0.519621;,
  0.400000;0.519621;,
  0.425000;0.519621;,
  0.450000;0.519621;,
  0.468302;0.519621;,
  0.475000;0.606176;,
  0.468302;0.606176;,
  0.468302;0.519621;,
  0.475000;0.519621;,
  0.475000;0.519621;,
  0.500000;0.519621;,
  0.525000;0.519621;,
  0.550000;0.519621;,
  0.575000;0.519621;,
  0.600000;0.519621;,
  0.600000;0.519621;,
  0.606698;0.519621;,
  0.606698;0.606176;,
  0.600000;0.606176;,
  0.606698;0.519621;,
  0.625000;0.519621;,
  0.375000;0.312500;,
  0.400000;0.312500;,
  0.425000;0.312500;,
  0.450000;0.312500;,
  0.468302;0.312500;,
  0.475000;0.312500;,
  0.500000;0.312500;,
  0.525000;0.312500;,
  0.550000;0.312500;,
  0.575000;0.312500;,
  0.600000;0.312500;,
  0.606698;0.312500;,
  0.625000;0.312500;,
  0.626409;0.935591;,
  0.548284;0.992353;,
  0.451716;0.992353;,
  0.373591;0.935591;,
  0.351745;0.868356;,
  0.343750;0.843750;,
  0.343750;0.843750;,
  0.373591;0.751909;,
  0.373591;0.751909;,
  0.343750;0.843750;,
  0.451716;0.695147;,
  0.451716;0.695147;,
  0.451716;0.695147;,
  0.548284;0.695147;,
  0.548284;0.695147;,
  0.626409;0.751909;,
  0.626409;0.751909;,
  0.548284;0.695147;,
  0.656250;0.843750;,
  0.656250;0.843750;,
  0.656250;0.843750;,
  0.648255;0.868356;,
  0.373591;0.751909;,
  0.626409;0.751909;,
  0.626409;0.751909;,
  0.373591;0.751909;,
  0.000000;0.166667;,
  0.166667;0.166667;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.166667;,
  0.333333;0.333333;,
  0.500000;0.166667;,
  0.500000;0.333333;,
  0.666667;0.166667;,
  0.666667;0.333333;,
  0.833333;0.166667;,
  0.833333;0.333333;,
  1.000000;0.166667;,
  1.000000;0.333333;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.500000;0.666667;,
  0.666667;0.666667;,
  0.833333;0.666667;,
  1.000000;0.666667;,
  0.166667;0.833333;,
  0.000000;0.833333;,
  0.333333;0.833333;,
  0.500000;0.833333;,
  0.666667;0.833333;,
  0.833333;0.833333;,
  1.000000;0.833333;,
  0.083333;0.000000;,
  0.250000;0.000000;,
  0.416667;0.000000;,
  0.583333;0.000000;,
  0.750000;0.000000;,
  0.916667;0.000000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;,
  0.000000;0.166667;,
  0.166667;0.166667;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.166667;,
  0.333333;0.333333;,
  0.500000;0.166667;,
  0.500000;0.333333;,
  0.666667;0.166667;,
  0.666667;0.333333;,
  0.833333;0.166667;,
  0.833333;0.333333;,
  1.000000;0.166667;,
  1.000000;0.333333;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.500000;0.666667;,
  0.666667;0.666667;,
  0.833333;0.666667;,
  1.000000;0.666667;,
  0.166667;0.833333;,
  0.000000;0.833333;,
  0.333333;0.833333;,
  0.500000;0.833333;,
  0.666667;0.833333;,
  0.833333;0.833333;,
  1.000000;0.833333;,
  0.083333;0.000000;,
  0.250000;0.000000;,
  0.416667;0.000000;,
  0.583333;0.000000;,
  0.750000;0.000000;,
  0.916667;0.000000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;,
  0.000000;0.166667;,
  0.166667;0.166667;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.166667;,
  0.333333;0.333333;,
  0.500000;0.166667;,
  0.500000;0.333333;,
  0.666667;0.166667;,
  0.666667;0.333333;,
  0.833333;0.166667;,
  0.833333;0.333333;,
  1.000000;0.166667;,
  1.000000;0.333333;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.500000;0.666667;,
  0.666667;0.666667;,
  0.833333;0.666667;,
  1.000000;0.666667;,
  0.166667;0.833333;,
  0.000000;0.833333;,
  0.333333;0.833333;,
  0.500000;0.833333;,
  0.666667;0.833333;,
  0.833333;0.833333;,
  1.000000;0.833333;,
  0.083333;0.000000;,
  0.250000;0.000000;,
  0.416667;0.000000;,
  0.583333;0.000000;,
  0.750000;0.000000;,
  0.916667;0.000000;,
  0.083333;1.000000;,
  0.250000;1.000000;,
  0.416667;1.000000;,
  0.583333;1.000000;,
  0.750000;1.000000;,
  0.916667;1.000000;;
 }
}
