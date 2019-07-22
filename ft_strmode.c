/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:58:35 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/22 12:48:36 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*ft_strmode(mode_t mode)
{
	char	*p;
	int		i;
	char	*head;
	mode_t mode_t;

	i = 0;
	p = malloc(sizeof(char) * 9);
	while (i < 9)
		p[i++] = '0';
	head = p;
	/*type*/
	mode_t = mode & S_IFMT; //masque du type de fichier
	if (S_ISDIR(mode_t)) /* directory */
		*(p++) = 'd';
	else if (S_ISCHR(mode_t)) /* character special */
		*(p++) = 'c';
	else if (S_ISBLK(mode_t)) /* block special */
		*(p++) = 'b';
	else if (S_ISREG(mode_t)) /* regular */
		*(p++) = '-';
	else if (S_ISLNK(mode_t))  /* symbolic link */
		*(p++) = 'l';
	else if (S_ISSOCK(mode_t)) /* socket */
		*(p++) = 's';
	else if (S_ISFIFO(mode_t)) /* fifo */
		*(p++) = 'p';
	else if  (S_ISWHT(mode_t))/* whiteout */
		*(p++) = 'w';
	else
		*(p++) = '?';
	/* usr			 */
	if (mode & S_IRUSR)
		*p++ = 'r';
	else
		*p++ = '-';
	if (mode & S_IWUSR)
		*p++ = 'w';
	else
		*p++ = '-';
	if (mode & (S_IXUSR | S_ISUID))
	{
		if (S_IXUSR)
			*p++ = 'x';
		else if (S_ISUID)
			*p++ = 'S';
		else if (S_IXUSR | S_ISUID)
			*p++ = 's';
		if (!S_IXUSR && !S_ISUID)
			*p++ = '-';
	}

	/* group */
	if (mode & S_IRGRP)
		*p++ = 'r';
	else
		*p++ = '-';
	if (mode & S_IWGRP)
		*p++ = 'w';
	else
		*p++ = '-';
	if (mode & (S_IXGRP | S_ISGID))
	{
		if (S_IXGRP)
			*p++ = 'x';
		else if (S_ISGID)
			*p++ = 'S';
		else if (S_IXGRP | S_ISGID)
			*p++ = 's';
		else
			*p++ = '-';
	}
	/* other */
	if (mode & S_IROTH)
		*p++ = 'r';
	else
		*p++ = '-';
	if (mode & S_IWOTH)
		*p++ = 'w';
	else
		*p++ = '-';
	//if (mode & (S_IXOTH | S_ISVTX))
	//{
		if (mode & S_IXOTH)
			*p++ = 'x';
		else
			*p++ = '-';
	/*	if (mode & S_ISVTX)
			*p++ = 'T';
		else if (S_IXOTH | S_ISVTX)
			*p++ = 't';
		else
			*p++ = '-';
	//}*/
	*p++ = ' ';/* will be a '+' if ACL's implemeented */
	*p = '\0';
//	printf("h = %s\n", head);
	return (head);
}
