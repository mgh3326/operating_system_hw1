signed __int64 __fastcall power(int a1)
{
  signed __int64 result; // rax

  switch ( a1 )
  {
    case 0:
      result = 1LL;
      break;
    case 1:
      result = 2LL;
      break;
    case 2:
      result = 4LL;
      break;
    case 3:
      result = 8LL;
      break;
    case 4:
      result = 16LL;
      break;
    case 5:
      result = 32LL;
      break;
    case 6:
      result = 64LL;
      break;
    case 7:
      result = 128LL;
      break;
    default:
      result = 0LL;
      break;
  }
  return result;
}
_BOOL8 __fastcall vGetBitValue(unsigned int a1, int a2)
{
  _BYTE *v2; // ST28_8
  char v3; // bl

  v2 = malloc(512uLL);
  DevOpenDisk(512LL);
  DevReadBlock(a1, v2);
  v3 = v2[a2 / 8];
  return (unsigned __int8)(v3 & (unsigned __int64)power(7 - a2 % 8)) != 0;
}
void __fastcall vGetInodeValue(int a1, _DWORD *a2)
{
  signed int i; // [rsp+1Ch] [rbp-14h]
  _DWORD *ptr; // [rsp+28h] [rbp-8h]

  ptr = malloc(0x200uLL);
  DevReadBlock((unsigned int)(a1 / 8 + 3), ptr);
  *a2 = ptr[16 * (signed __int64)(a1 % 8)];
  a2[1] = ptr[16 * (signed __int64)(a1 % 8) + 1];
  for ( i = 0; i <= 13; ++i )
    a2[i + 2] = ptr[16 * (signed __int64)(a1 % 8) + 2 + i];
  free(ptr);
}