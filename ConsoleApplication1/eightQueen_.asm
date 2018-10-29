	.model flat,c
	.code

eightQueen_ proc

	push ebp
	mov ebp,esp
	push esi
	push edi
	push edx
	push ecx
	push ebx

	mov esi,[ebp+8]		;a[i]
	xor eax,eax
L1:
	mov edi,[esi+eax*4]
	add edi,1			;a[i]++
	cmp edi,9
	jne L2
	mov edi,0
	mov [esi+eax*4],edi	;�����������Ϊ0��������һ��
	sub eax,1
	jmp L1
		
L2:	mov [esi+eax*4],edi	;��д
	add eax,1			;i++

L3:	mov edi,[esi+eax*4]	;a[i]++
	add edi,1
	cmp edi,9
	jne L4
	mov edi,0			;�����������Ϊ0��������һ��
	mov [esi+eax*4],edi
	sub eax,1
	jmp L3

L4:	mov [esi+eax*4],edi	;��д
	mov ebx,1			;ebx=j=1
	
;��ʼ��ǰ�����бȽ�
L5:	mov edx,eax			;edx=i
	sub edx,ebx			;edx=i-j
	mov ecx,[esi+eax*4]	;ecx=a[i]
	cmp ecx,[esi+edx*4]	
	jae LA				;a[i]>=a[i-j]

	mov ecx,[esi+edx*4]
	sub ecx,[esi+eax*4]	;ecx=a[i-j]-a[i]
	jmp LB
LA: sub ecx,[esi+edx*4]	;ecx=a[i]-a[i-j]

LB:	cmp ecx,0			;a[i]==a[i-j]
	je L3
	cmp ecx,ebx			;ecx==ebx �� ��һ��б����
	je L3
	;���������� �� ��L3 a[i]++

	add ebx,1			;j++
	cmp ebx,eax			;while j<=i 
	jle L5
;�ȽϽ���9

	add eax,1		;��һ��
	cmp eax,8		;end
	jne L3

	pop ebx
	pop ecx
	pop edx
	pop edi
	pop esi
	pop ebp
	ret

eightQueen_ endp
	end