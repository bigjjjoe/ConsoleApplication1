	.model flat,c
	.code


CanIGo_ proc
		push ebp
		mov ebp,esp
		push edi
		push esi
		push edx
		push ecx
		push ebx
		mov eax,0
		mov ebx,[ebp+8]
		cmp ebx,0
		jb L2
		cmp ebx,8
		jae L2

		mov ecx,[ebp+12]
		cmp ecx,0
		jb L2
		cmp ecx,8
		jae L2

		imul ebx,8
		add ebx,ecx			;i*8+j
		mov esi,[ebp+16]	;board
		mov edi,[ebp+20]	;Htry
		mov edx,0			;k—≠ª∑

		mov ecx,[esi+ebx*4]
		cmp ecx,0
		jne L2

	L1:
		mov ebx,[ebp+8]
		add ebx,[edi+edx*4]
		cmp ebx,0
		jb cannot
		cmp ebx,8
		jae cannot

		mov ecx,[ebp+12]
		add ecx,[edi+edx*4+32]
		cmp ecx,0
		jb cannot
		cmp ecx,8
		jae cannot

		imul ebx,8
		add ebx,ecx
				
		mov ecx,[esi+ebx*4]
		cmp ecx,0
		jne cannot
		inc eax
	cannot:
		inc edx
		cmp edx,8
		jb L1 

	L2:
		pop ebx
		pop ecx
		pop edx
		pop esi
		pop edi
		pop ebp
		ret

CanIGo_ endp
	end