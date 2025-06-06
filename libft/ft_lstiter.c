/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:34:20 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:47:27 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>

// // ノードの内容を表示する関数
// void	print_content(void *content)
// {
// 	printf("Content: %s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;

// 	// ノード1とノード2を作成
// 	node1 = ft_lstnew(malloc(20));
// 	node2 = ft_lstnew(malloc(20));
// 	if (node1 == NULL || node1->content == NULL || node2 == NULL
// 		|| node2->content == NULL)
// 	{
// 		printf("Failed to allocate memory\n");
// 		return (1);
// 	}
// 	// ノードの内容に文字列を設定
// 	snprintf(node1->content, 20, "First Node");
// 	snprintf(node2->content, 20, "Second Node");
// 	// ノードを連結
// 	node1->next = node2;
// 	// リストの内容を出力するためにft_lstiterを使用
// 	printf("Iterating through the list:\n");
// 	ft_lstiter(node1, print_content); // リストの各ノードにprint_contentを適用
// 	// メモリ解放
// 	free(node1->content);
// 	free(node2->content);
// 	free(node1);
// 	free(node2);
// 	return (0);
// }
