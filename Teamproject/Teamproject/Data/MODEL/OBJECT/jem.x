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
 34;
 1.56825;4.88202;-2.01640;,
 0.00000;3.47842;-2.01640;,
 0.00000;7.04642;-2.01640;,
 1.86286;7.06769;-2.01640;,
 -1.56825;4.88202;-2.01640;,
 -1.86286;7.06769;-2.01640;,
 0.00000;10.98084;-2.01640;,
 1.73058;8.94453;-2.01640;,
 -1.73058;8.94453;-2.01640;,
 0.00000;14.46935;-0.43964;,
 0.00000;14.46935;0.43964;,
 3.33996;10.53934;0.43964;,
 3.33996;10.53934;-0.43964;,
 -3.33996;10.53934;-0.43964;,
 -3.33996;10.53934;0.43964;,
 1.73058;8.94453;2.01640;,
 0.00000;10.98084;2.01640;,
 0.00000;7.04437;2.01640;,
 1.86286;7.06769;2.01640;,
 -1.73058;8.94453;2.01640;,
 -1.86286;7.06769;2.01640;,
 0.00000;3.47842;2.01640;,
 1.56825;4.88202;2.01640;,
 -1.56825;4.88202;2.01640;,
 0.00000;-0.01010;0.43964;,
 0.00000;-0.01010;-0.43964;,
 3.02667;2.69882;-0.43964;,
 3.02667;2.69882;0.43964;,
 -3.02667;2.69882;0.43964;,
 -3.02667;2.69882;-0.43964;,
 -3.59526;6.91708;0.43964;,
 -3.59526;6.91708;-0.43964;,
 3.59526;6.91708;0.43964;,
 3.59526;6.91708;-0.43964;;
 
 32;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;13,14,10,9;,
 4;15,16,17,18;,
 4;16,19,20,17;,
 4;18,17,21,22;,
 4;17,20,23,21;,
 4;24,25,26,27;,
 4;28,29,25,24;,
 4;30,31,29,28;,
 4;13,31,30,14;,
 4;32,27,26,33;,
 4;12,11,32,33;,
 4;26,25,1,0;,
 4;33,26,0,3;,
 4;25,29,4,1;,
 4;29,31,5,4;,
 4;9,12,7,6;,
 4;12,33,3,7;,
 4;31,13,8,5;,
 4;13,9,6,8;,
 4;11,10,16,15;,
 4;32,11,15,18;,
 4;10,14,19,16;,
 4;14,30,20,19;,
 4;24,27,22,21;,
 4;27,32,18,22;,
 4;30,28,23,20;,
 4;28,24,21,23;;
 
 MeshMaterialList {
  1;
  32;
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
  0;;
  Material {
   0.968627;1.000000;1.000000;1.000000;;
   2.000000;
   1.000000;1.000000;1.000000;;
   0.280902;0.290000;0.290000;;
   TextureFilename {
    "C:\\Users\\81902\\Desktop\\git?V\\SarinaHayashikawaGames\\?g?c?w???????r?W?l?X?????w?Z_??????????\\04_???i?A?u???b?N?E?H?[?Y?i?????r???j\\01_?J??????\\3D?A?N?V??????????\\3DGameProject\\3DGameProject\\Data\\TEXTURE\\ITEM\\jem.png";
   }
  }
 }
 MeshNormals {
  41;
  0.885557;-0.369039;-0.282134;,
  0.581135;-0.649304;-0.490598;,
  -0.885557;-0.369039;-0.282134;,
  0.913693;-0.028958;-0.405373;,
  -0.913693;-0.028958;-0.405373;,
  0.830223;0.328613;-0.450269;,
  0.675629;0.574190;-0.462419;,
  -0.830223;0.328613;-0.450269;,
  0.830223;0.328613;0.450269;,
  0.675629;0.574190;0.462419;,
  -0.830223;0.328613;0.450269;,
  0.913693;-0.028958;0.405373;,
  -0.913693;-0.028958;0.405373;,
  0.885557;-0.369039;0.282134;,
  0.581135;-0.649304;0.490598;,
  -0.786983;-0.399384;0.470266;,
  0.358077;-0.168510;-0.918360;,
  0.000000;-0.203950;-0.978981;,
  0.000000;0.000000;-1.000000;,
  0.359744;-0.011334;-0.932982;,
  -0.358077;-0.168510;-0.918360;,
  -0.359744;-0.011334;-0.932982;,
  0.000000;0.199550;-0.979888;,
  0.394053;0.148361;-0.907034;,
  -0.394053;0.148361;-0.907034;,
  0.394053;0.148361;0.907034;,
  0.000000;0.199550;0.979888;,
  0.000000;0.000000;1.000000;,
  0.359744;-0.011334;0.932982;,
  -0.394053;0.148361;0.907034;,
  -0.359744;-0.011334;0.932982;,
  0.000000;-0.203950;0.978981;,
  0.358077;-0.168510;0.918360;,
  -0.358077;-0.168510;0.918360;,
  -0.675629;0.574190;0.462419;,
  -0.675629;0.574190;-0.462419;,
  -0.581135;-0.649304;-0.490598;,
  -0.581135;-0.649304;0.490598;,
  0.345876;-0.386450;-0.855001;,
  -0.345876;-0.386450;-0.855001;,
  0.345876;-0.386450;0.855001;;
  32;
  4;16,17,18,19;,
  4;17,20,21,18;,
  4;19,18,22,23;,
  4;18,21,24,22;,
  4;6,9,8,5;,
  4;7,10,34,35;,
  4;25,26,27,28;,
  4;26,29,30,27;,
  4;28,27,31,32;,
  4;27,30,33,31;,
  4;14,1,0,13;,
  4;15,2,36,37;,
  4;12,4,2,15;,
  4;7,4,12,10;,
  4;11,13,0,3;,
  4;5,8,11,3;,
  4;38,1,17,16;,
  4;3,0,16,19;,
  4;36,39,20,17;,
  4;2,4,21,20;,
  4;6,5,23,22;,
  4;5,3,19,23;,
  4;4,7,24,21;,
  4;7,35,22,24;,
  4;8,9,26,25;,
  4;11,8,25,28;,
  4;34,10,29,26;,
  4;10,12,30,29;,
  4;14,40,32,31;,
  4;13,11,28,32;,
  4;12,15,33,30;,
  4;15,37,31,33;;
 }
 MeshTextureCoords {
  34;
  0.595885;0.603023;,
  0.500000;0.688840;,
  0.500000;0.470689;,
  0.613897;0.469389;,
  0.404115;0.603023;,
  0.386103;0.469389;,
  0.500000;0.230135;,
  0.605809;0.354637;,
  0.394191;0.354637;,
  0.500000;0.016844;,
  0.500000;0.016844;,
  0.704208;0.257129;,
  0.704208;0.257129;,
  0.295792;0.257129;,
  0.295792;0.257129;,
  0.605809;0.354637;,
  0.500000;0.230135;,
  0.500000;0.470815;,
  0.613897;0.469389;,
  0.394191;0.354637;,
  0.386103;0.469389;,
  0.500000;0.688840;,
  0.595885;0.603023;,
  0.404115;0.603023;,
  0.500000;0.902132;,
  0.500000;0.902132;,
  0.685054;0.736506;,
  0.685054;0.736506;,
  0.314946;0.736506;,
  0.314946;0.736506;,
  0.280182;0.478597;,
  0.280182;0.478597;,
  0.719818;0.478597;,
  0.719818;0.478597;;
 }
}
