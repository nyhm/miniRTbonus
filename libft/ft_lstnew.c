/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:07:18 by hnagashi          #+#    #+#             */
/*   Updated: 2024/10/24 20:11:11 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// #include <stdio.h>

// int	main(void)
// {
// 	// ノードを作成する
// 	char *content = "Hello, world!";
// 	t_list *node = ft_lstnew(content);

// 	// ノードが正常に作成されたか確認
// 	if (node != NULL)
// 	{
// 		printf("ノードが作成されました！\n");
// 		printf("content: %s\n", (char *)node->content); // ノードのcontentを表示
// 		printf("next: %p\n", (void *)node->next);
// 		// ノードのnextを表示（NULLであるべき）
// 	}
// 	else
// 	{
// 		printf("ノードの作成に失敗しました。\n");
// 	}

// 	// メモリを解放
// 	free(node); // メモリを解放することを忘れない

// 	return (0);
// }